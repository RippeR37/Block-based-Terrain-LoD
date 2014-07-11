#include "Keyboard.h"
#include "../Game.h"

namespace Input {

    CKeyboard::CKeyboard() { }

    CKeyboard::~CKeyboard() { }

    void CKeyboard::Init() {
        glfwSetKeyCallback(CGame::Get().Window().GetWindow(), CKeyboard::ProcessInput);
    }

    void CKeyboard::ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if(action == GLFW_PRESS) {
            if(key == GLFW_KEY_ESCAPE) {
                glfwSetWindowShouldClose(window, GL_TRUE);
            }
        }
    }

}
