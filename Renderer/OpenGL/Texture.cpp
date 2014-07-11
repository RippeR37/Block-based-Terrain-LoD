#include <fstream>
#include <iostream>
#include <png.h>
#include <jpeglib.h>

#include "Texture.h"
#include "../../Common/File.h"
#include "../../Common/Data.h"

namespace OpenGL {

    CTexture::CTexture() {
        m_textureID = 0;
    }

    CTexture::~CTexture() {
        if(m_textureID != 0)
            glDeleteTextures(1, &m_textureID);
    }

    void CTexture::LoadTexture(const std::string filePath) {
        /*** Variables ***/
        std::string fileExt;

        /*** Implementation ***/
        if(filePath.size() < 5) {
            std::cerr << "OGL::Texture | Invalid path to texture: '" << filePath << "'" << std::endl;
            return;
        }

        fileExt = Common::CFile::GetFileExtension(filePath);

        if(fileExt == "bmp") {
            LoadTextureFromBMP(filePath);
        } else if(fileExt == "tga") {
            LoadTextureFromTGA(filePath);
        } else if(fileExt == "png") {
            LoadTextureFromPNG(filePath);
        } else if(fileExt == "jpg") {
            LoadTextureFromJPG(filePath);
        } else {
            std::cerr << "OGL::Texture | Unrecognized file extension: '" << fileExt << "'" << std::endl;
        }
    }

    void CTexture::Bind(GLuint UniformID, int index) {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glUniform1i(UniformID, index);
    }

    void CTexture::LoadTextureFromBMP(const std::string& filePath) {
        /*** Variables ***/
        int bits;
        int width;
        int height;
        int dataPos;
        int imageSize;

        unsigned char header[54];
        unsigned char *data;

        GLuint type_a, type_b;
        std::ifstream fileStream;

        /*** Implementation ***/
        fileStream.open(filePath, std::ifstream::in | std::ifstream::binary);

        if(fileStream.is_open() == false) {
            std::cerr << "OGL::Texture | Could not open texture file (" << filePath << ")" << std::endl;
            return;
        }

        fileStream.read((char*)header, 54);
        if(!fileStream || header[0] != 'B' || header[1] != 'M') {
            std::cerr << "OGL::Texture | Could not read valid BMP header" << std::endl;
            return;
        }

        //bits = *(reinterpret_cast<unsigned short int*>(&header[28]));     // <-- strict aliasing warning
        bits = Common::CData::readCharsAsShort((char*)&header[28]);

        if(bits == 24) {
            type_a = GL_RGB;
            type_b = GL_BGR;
            bits = 3;
        } else if(bits == 32) {
            type_a = GL_RGBA;
            type_b = GL_BGRA;
            bits = 4;
        } else {
            std::cerr << "OGL::Texture | Wrong bpp data: " << bits << std::endl;
            return;
        }

        /// these produces strict-aliasing warning, but still works!
        //dataPos     = *(reinterpret_cast<unsigned int*>(&header[10]));
        //width       = *(reinterpret_cast<unsigned int*>(&header[18]));
        //height      = *(reinterpret_cast<unsigned int*>(&header[22]));
        //imageSize   = *(reinterpret_cast<unsigned int*>(&header[34]));

        dataPos     = Common::CData::readCharsAsInt((char*)&header[10]);
        width       = Common::CData::readCharsAsInt((char*)&header[18]);
        height      = Common::CData::readCharsAsInt((char*)&header[22]);
        imageSize   = Common::CData::readCharsAsInt((char*)&header[34]);

        if(imageSize == 0)
            imageSize = width*height*bits;

        if(dataPos == 0)
            dataPos = 54;

        data = new unsigned char[imageSize];

        fileStream.seekg(dataPos);
        fileStream.read((char*)data, imageSize);
        fileStream.close();

        m_textureID = 0;
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, type_a, width, height, 0, type_b, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        m_isLoaded = true;
        delete [] data;
    }

    void CTexture::LoadTextureFromTGA(const std::string& filePath) {
        /*** Variables ***/
        std::ifstream fileStream;
        char buff[256];
        char c;
        char si_a[2];
        char* si = (char*)&si_a[0];
        int id_len, cm_type, type;
        int cm_len; //cm_offset, cm_bpp;
        int width, height; //x_or, y_or;
        int bits, c_mode, img_size; //desc;
        unsigned char *data;
        GLuint type_a, type_b;


        /*** Implementation ***/
        fileStream.open(filePath, std::fstream::in | std::fstream::binary);
        if(fileStream.is_open() == false) {
            std::cerr << "OGL::Texture | Could not open texture file (" << filePath << ")" << std::endl;
        }

        fileStream.read(&c, 1);         id_len      = (int)c;
        fileStream.read(&c, 1);         cm_type     = (int)c;
        fileStream.read(&c, 1);         type        = (int)c;
        fileStream.read(si, 2);
        fileStream.read(si, 2);         cm_len      = Common::CData::readCharsAsShort(si);
        fileStream.read(&c, 1);
        fileStream.read(si, 2);
        fileStream.read(si, 2);
        fileStream.read(si, 2);         width       = Common::CData::readCharsAsShort(si);
        fileStream.read(&c, 1);         height      = Common::CData::readCharsAsShort(si);
        fileStream.read(&c, 1);         bits        = (int)c;
        fileStream.read(&c, 1);

        c_mode   = bits / 8;
        img_size = width * height * c_mode;

        if(type != 2 && type != 3) {
            std::cerr << "OGL::Texture | Unsupported TGA file type: " << type << std::endl;
            return;
        }

        if(c_mode != 3 && c_mode != 4) {
            std::cerr << "OGL::Texture | Unsupported TGA color bits: " << c_mode << std::endl;
            return;
        } else {
            if(c_mode == 3) { type_a = GL_RGB8;     type_b = GL_BGR;  }
            else            { type_a = GL_RGBA8;    type_b = GL_BGRA; }
        }

        /// Optional fields
        if(id_len > 0)
            fileStream.read(buff, id_len);
        if(cm_type != 0 && cm_len > 0)
            fileStream.read(buff, cm_len);

        /*** Main data reading ***/
        data = new unsigned char[img_size];
        fileStream.read((char*)data, img_size);
        fileStream.close();

        /*** OpenGL textutre creation ***/
        m_textureID = 0;
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, type_a, width, height, 0, type_b, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        m_isLoaded = true;
        delete[] data;
    }

    /** Comment:
     * Since libPNG rely on C-style file I/O (FILE* struct),
     * we have to use it here to load image data
    **/
    void CTexture::LoadTextureFromPNG(const std::string& filePath) {
        /*** Variables ***/
        GLint format;
        int bit_depth;
        int color_type;
        int rowbytes;
        png_byte header[8];
        png_uint_32 width;
        png_uint_32 height;

        /*** Implementation ***/
        FILE *fp = fopen(filePath.c_str(), "rb");
        if(fp == 0) {
            std::cerr << "OGL::Texture | Failed to load texture file: " << filePath << std::endl;
            return;
        }

        fread(header, 1, 8, fp);
        if(png_sig_cmp(header, 0, 8)) {
            std::cerr << "OGL::Texture | Loaded file is not PNG image!" << std::endl;
            fclose(fp);
            return;
        }

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr) {
            std::cerr << "OGL::Texture | pngCreateReadStrcut returned 0!" << std::endl;
            fclose(fp);
            return;
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
            std::cerr << "OGL::Texture | pngCreateReadStruct return 0!" << std::endl;
            png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
            fclose(fp);
            return;
        }

        png_infop end_info = png_create_info_struct(png_ptr);
        if (!end_info) {
            std::cerr << "OGL::Texture | pngCreateInfoStruct return 0!" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
            fclose(fp);
            return;
        }

        if (setjmp(png_jmpbuf(png_ptr))) {
            std::cerr << "OGL::Texture | Error with setjmp()!" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return;
        }

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);
        png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

        if (bit_depth != 8) {
            std::cerr << "OGL::Texture | Unsupported bit depth (" << bit_depth << ")" << std::endl;
            return;
        }

        switch(color_type) {
            case PNG_COLOR_TYPE_RGB:
                format = GL_RGB;
                break;
            case PNG_COLOR_TYPE_RGB_ALPHA:
                format = GL_RGBA;
                break;
            default:
                std::cerr << "OGL::Texture | Unknown libpng color type: " << color_type << std::endl;
                return;
        }

        png_read_update_info(png_ptr, info_ptr);
        rowbytes  = png_get_rowbytes(png_ptr, info_ptr);
        rowbytes += 3 - ((rowbytes-1) % 4);

        png_byte* image_data = new png_byte[rowbytes * height + 15];
        if (image_data == NULL) {
            std::cerr << "OGL::Texture | Could not allocate memory for PNG image data" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return;
        }

        png_byte** row_pointers = new png_byte*[height];
        if(row_pointers == NULL) {
            std::cerr << "OGL::Texture | Could not allocate memory for PNG row pointers!" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            delete[] image_data;
            fclose(fp);
            return;
        }

        for(unsigned int i = 0; i < height; i++) {
            row_pointers[height - 1 - i] = image_data + i * rowbytes;
        }
        png_read_image(png_ptr, row_pointers);

        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        /// Cleaning up
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] image_data;
        delete[] row_pointers;
        fclose(fp);
        m_isLoaded = true;
    }

    void CTexture::LoadTextureFromJPG(const std::string& filePath) {
        /*** Variables ***/
        FILE *fd;
        unsigned int width;
        unsigned int height;
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;
        char* line;
        char* data;
        GLint format = GL_RGB;

        /*** Implementation ***/
        cinfo.err = jpeg_std_error (&jerr);
        jpeg_create_decompress (&cinfo);

        fd = fopen(filePath.c_str(), "rb");
        if(fd == 0) {
            std::cerr << "OGL::Texture | JPG #1" << std::endl;
            return;
        }

        jpeg_stdio_src (&cinfo, fd);
        jpeg_read_header (&cinfo, TRUE);

        width  = cinfo.image_width;
        height = cinfo.image_height;

        if (GL_RGB == format) {
            if (cinfo.out_color_space == JCS_GRAYSCALE) {
                std::cerr << "OGL::Texture | JPG #2" << std::endl;
                return;
            }
        } else if (cinfo.out_color_space != JCS_GRAYSCALE) {
            std::cerr << "OGL::Texture | JPG #3" << std::endl;
            return;
        }

        data = new char[width * height * 3];

        jpeg_start_decompress (&cinfo);
        while (cinfo.output_scanline < cinfo.output_height) {
            line = &data[0] + 3 * width * cinfo.output_scanline;
            jpeg_read_scanlines (&cinfo, &line, 1);
        }

        jpeg_finish_decompress (&cinfo);
        jpeg_destroy_decompress (&cinfo);
        fclose(fd);

        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        delete[] data;
        m_isLoaded = true;
    }

}
