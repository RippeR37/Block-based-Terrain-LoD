#include "Window.h"
#include "../Game.h"

#include <cstdio>

namespace GUI {

    CWindow::CWindow() {
        m_isCreated = false;
    }

    CWindow::~CWindow() {
        if(isCreated()) {
            Close();
        }
    }

    void CWindow::InitWindow(int width, int height, std::string title) {
        m_width  = width;
        m_height = height;
        m_title  = title;

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT , GL_TRUE);

        m_window = glfwCreateWindow(Width(), Height(), Title().c_str(), NULL, NULL);
        if(!m_window) {
            std::cerr << "GUI::Window | Failed to create window" << std::endl;
            Close();
            return;
        }

        m_isCreated = true;
        glewExperimental = GL_TRUE;
        glfwMakeContextCurrent(m_window);
        if(glewInit() != GLEW_OK)
            std::cerr << "GUI::Window | Failed to initialize GLEW" <<  std::endl;

        /**
         * This hides GLFW bug that makes GL_INVALID_ENUM error to appear (1280)
        **/
        GLenum err = glGetError();
        if(err != GL_NO_ERROR && err != 1280) {
            std::cout << "OpenGL Error: " << err << "\n";
        }
    }

    void CWindow::InitGLFW() {
        if(glfwInit() == 0)
            std::cerr << "GUI::Window | Failed to initialize GLFW" << std::endl;
    }

    void CWindow::Update() {
        /*** Variables ***/
        static char title[70];
        static double accumulator = 0.0;
        static int frames = 0;

        /*** Updating title ***/
        accumulator += CGame::Get().getDT();
        ++frames;
        if(accumulator > 1.0) {
            snprintf(title, 70, "%s | FPS: %d | DT: %g ms", Title().c_str(), frames, 1000 * accumulator / (float)frames);
            glfwSetWindowTitle(m_window, title);
            accumulator = 0.0;
            frames = 0;
        }

        /*** Updating buffers and polling I/O events ***/
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void CWindow::Close() {
        m_isCreated = false;

        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}
