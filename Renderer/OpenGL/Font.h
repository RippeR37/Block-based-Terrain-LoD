#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGL {

    struct charInfo {
        float l, r;
        float h, w;
        float ax;
    };

    class CFont {
        public:
            CFont();
            ~CFont();

            void Init();
            void Dispose();
            void LoadFont(std::string filePath, int size);

            int GetOriginalSize()           { return m_genSize; }
            int VerticalPadding()           { return m_vertPadding; }
            GLuint GetTex()                 { return m_textureID; }
            charInfo& ci(char c)            { return m_characters[(int)c]; }

        private:
            int         m_vertPadding;
            int         m_genSize;
            GLuint      m_textureID;
            charInfo    m_characters[128];

            FT_Face     m_ftface;
            FT_Library  m_ftlib;
    };

}

#endif // FONT_H_INCLUDED
