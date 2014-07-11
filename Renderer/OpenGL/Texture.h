#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGL {

    class CTexture {
        public:
            CTexture();
            ~CTexture();

            void LoadTexture(const std::string filePath);
            void Bind(GLuint UniformID, int index = 0);

            bool   isLoaded()   { return m_isLoaded; }
            GLuint getTex()     { return m_textureID; }

        private:
            /*** Methods ***/
            void LoadTextureFromBMP(const std::string& filePath);
            void LoadTextureFromTGA(const std::string& filePath);
            void LoadTextureFromPNG(const std::string& filePath);
            void LoadTextureFromJPG(const std::string& filePath);

            /*** Variables ***/
            bool    m_isLoaded;
            GLuint  m_textureID;
    };

}

#endif // TEXTURE_H_INCLUDED
