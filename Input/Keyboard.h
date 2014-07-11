#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace Input {

    class CKeyboard {
        public:
            CKeyboard();
            ~CKeyboard();

            void Init();
            static void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods);

        private:
            //
    };

}

#endif // KEYBOARD_H_INCLUDED
