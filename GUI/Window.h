#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <string>
#include <iostream>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace GUI {

    class CWindow {
        public:
            CWindow();
            ~CWindow();

            void InitWindow(int width, int height, std::string title);
            void InitGLFW();
            void Update();
            void Close();

            int& Width()            { return m_width;  }
            int& Height()           { return m_height; }
            bool isCreated()        { return m_isCreated; }
            std::string& Title()    { return m_title;  }
            GLFWwindow* GetWindow() { return m_window; }

        private:
            int             m_width;
            int             m_height;
            bool            m_isCreated;
            std::string     m_title;

            GLFWwindow*     m_window;
    };

}

#endif // WINDOW_H_INCLUDED
