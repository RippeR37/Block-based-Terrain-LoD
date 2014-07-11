#include "Font.h"
#include <iostream>

namespace OpenGL {

    CFont::CFont() {
        m_textureID   = 0;
        m_vertPadding = 0;
    }

    CFont::~CFont() {
        Dispose();
    }

    void CFont::Init() { }

    void CFont::Dispose() {
        if(m_textureID != 0)
            glDeleteTextures(1, &m_textureID);
    }

    void CFont::LoadFont(std::string fontPath, int size) {
        int w = 0;
        int h = 0;
        int max_height = 0;

        if(FT_Init_FreeType(&m_ftlib)) {
            std::cerr << "OGL::Font | FreeType2 initialization failed!" << std::endl;
            return;
        }

        m_genSize = size;
        if(FT_New_Face(m_ftlib, fontPath.c_str(), 0, &m_ftface)) {
            std::cerr << "OGL::Font | Failed to load font '" << fontPath.c_str() << "'" << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(m_ftface, 0, size);
        FT_GlyphSlot g = m_ftface->glyph;

        for(int i = 32; i < 128; ++i) {
            if(FT_Load_Char(m_ftface, i, FT_LOAD_RENDER)) {
                std::cerr << "OGL::Font | Failed to load character '" << (char)i << "'" << std::cerr;
                continue;
            }
            w += g->bitmap.width + 1;
            h = std::max(h, g->bitmap.rows);

            if(g->metrics.height > max_height) {
                max_height = g->metrics.height;
                m_vertPadding = (g->metrics.height - g->metrics.horiBearingY) / 64;
            }
        }

        h += 4;
        m_vertPadding += 2;

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

        int x = 0;
        for(int i = 32; i < 128; i++) {
            if(FT_Load_Char(m_ftface, i, FT_LOAD_RENDER))
                continue;

            glTexSubImage2D(GL_TEXTURE_2D, 0, x, h - g->metrics.horiBearingY/64 - m_vertPadding, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

            m_characters[i].l = (float)x / (float)w;
            m_characters[i].r = (float)(x + g->bitmap.width) / (float)w;
            m_characters[i].h = h;
            m_characters[i].w = g->bitmap.width;
            m_characters[i].ax = g->advance.x >> 6;

            x += g->bitmap.width + 1;
        }

    }

}
