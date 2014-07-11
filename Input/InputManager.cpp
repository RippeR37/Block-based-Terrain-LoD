#include "InputManager.h"

namespace Input {

    CInputManager::CInputManager() {
        m_keyboard = new CKeyboard();
        m_mouse = new CMouse();
    }

    CInputManager::~CInputManager() {
        delete m_keyboard;
        delete m_mouse;
    }

    void CInputManager::Init() {
        m_keyboard->Init();
        m_mouse->Init();
    }

}
