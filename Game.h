#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GUI/Window.h"
#include "Logic/ApplicationLogic.h"
#include "Renderer/Renderer.h"
#include "Input/InputManager.h"

class CGame {
    public:
        /*** Singleton implementation ***/
        static CGame& Get() {
            static CGame game;
            return game;
        }

        /*** Main public methods ***/
        void Init();
        void Start();
        void End();

        /*** Setters ***/
        void setEnd()                           { m_end = true; }
        void setDT(double dt)                   { m_dt = dt; }

        /*** Getters ***/
        bool isEnd()                            { return m_end; }
        double getDT()                          { return m_dt; }

        /*** Access modules methods ***/
        GUI::CWindow&           Window()        { return *m_window; }
        Input::CInputManager&   Input()         { return *m_input;  }
        Rendering::CRenderer&   Renderer()      { return *m_renderer; }

    private:
        /*** Private methods ***/
        CGame();
        ~CGame();

        /*** Modules objects ***/
        GUI::CWindow*               m_window;
        Input::CInputManager*       m_input;
        Rendering::CRenderer*       m_renderer;

        /*** Variables ***/
        bool                        m_end;
        double                      m_dt;
};

#endif // GAME_H_INCLUDED
