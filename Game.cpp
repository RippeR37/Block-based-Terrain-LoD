#include <iostream>
#include "Game.h"

CGame::CGame() {
    m_window        = new GUI::CWindow();
    m_renderer      = new Rendering::CRenderer();
    m_input         = new Input::CInputManager();
    m_end           = false;
}

CGame::~CGame() {
    delete m_renderer;
    delete m_window;
    delete m_input;
}

void CGame::Init() {
    /*** Init libraried used by application such as GLFW, WinSock2 (Windows only) etc. ***/
    Logic::CApplicationLogic::InitLibraries();

    /*** Init application logic. This means creating window and initialization of input callbacks. ***/
    Logic::CApplicationLogic::Init();

    /*** Init Renderer ***/
    Renderer().Init();
}

void CGame::Start() {
    /*** Main loop ***/
    while(glfwWindowShouldClose(Window().GetWindow()) == false) {
        /*** Game logic update ***/
        Logic::CApplicationLogic::Update();

        /*** Rendering ***/
        Renderer().Render();

        /*** Window update ***/
        Window().Update();
    }
}

void CGame::End() {
    Logic::CApplicationLogic::Close();
}
