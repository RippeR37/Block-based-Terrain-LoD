#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace Input {

    class CMouse {
        public:
            CMouse();
            ~CMouse();

            void Init();

            /*** Setters ***/
            void setX(int x) { m_x = x; }
            void setY(int y) { m_y = y; }

            /*** Getters ***/
            int getX() { return m_x; }
            int getY() { return m_y; }

            /*** Static functions for GLFW to handle callbacks ***/
            static void ProcessMouseButtons(GLFWwindow* window, int button, int action, int mods);
            static void ProcessCursorMovement(GLFWwindow* window, double x, double y);

        private:
            int m_x;
            int m_y;
    };

}

#endif // MOUSE_H_INCLUDED
