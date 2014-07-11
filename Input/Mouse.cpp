#include "Mouse.h"
#include "..\Game.h"

namespace Input {

    CMouse::CMouse() { }

    CMouse::~CMouse() { }

    void CMouse::Init() {
        glfwSetCursorPosCallback(CGame::Get().Window().GetWindow(), CMouse::ProcessCursorMovement);

        glfwSetInputMode(CGame::Get().Window().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        glfwSetCursorPos(CGame::Get().Window().GetWindow(),
                         CGame::Get().Window().Width() /2,
                         CGame::Get().Window().Height()/2);
    }

    void CMouse::ProcessCursorMovement(GLFWwindow* window, double x, double y) {
        int wndWmid = CGame::Get().Window().Width()  / 2;
        int wndHmid = CGame::Get().Window().Height() / 2;

        CGame::Get().Input().Mouse().setX(x);
        CGame::Get().Input().Mouse().setY(y);

        CGame::Get().Renderer().Camera().UpdateMouse(x - wndWmid, y - wndHmid);
        glfwSetCursorPos(window, wndWmid, wndHmid);
    }

}
