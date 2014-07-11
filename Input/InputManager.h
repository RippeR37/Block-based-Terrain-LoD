#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include "Keyboard.h"
#include "Mouse.h"

namespace Input {

    class CInputManager{
        public:
            CInputManager();
            ~CInputManager();

            void Init();

            CKeyboard&  Keyboard()  { return *m_keyboard; }
            CMouse&     Mouse()     { return *m_mouse; }

        private:
            CKeyboard*      m_keyboard;
            CMouse*         m_mouse;
    };

}

#endif // INPUTMANAGER_H_INCLUDED
