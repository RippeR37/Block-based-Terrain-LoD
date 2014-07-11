#include "ApplicationLogic.h"
#include "../Game.h"

namespace Logic {

    void CApplicationLogic::Init() {
        CGame::Get().Window().InitWindow(800, 600, "Block based Terrain Level of Detail demo");
        CGame::Get().Input().Init();
    }

    void CApplicationLogic::Update() {
        /*** Time (delta) update ***/
        static double time_now, time_last_frame = glfwGetTime();
        time_now = glfwGetTime();
            CGame::Get().setDT(time_now - time_last_frame);
        time_last_frame = time_now;
    }

    void CApplicationLogic::Close() {
        CGame::Get().Window().Close();
        CGame::Get().setEnd();
    }

    void CApplicationLogic::InitLibraries() {
        CGame::Get().Window().InitGLFW();                   /// Init GLFW 3.0 (currentyl 3.0.4)
    }

}
