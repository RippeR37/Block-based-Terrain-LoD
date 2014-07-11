#include "Renderer.h"
#include "../Game.h"
#include <iostream>

namespace Rendering {

    CRenderer::CRenderer() {
        m_pipeline  = new OpenGL::CPipeline();
        m_shader    = new OpenGL::CShader();

        m_terrain   = new CTerrain();
        m_camera    = new CFreeCamera();
    }

    CRenderer::~CRenderer() {
        delete m_camera;
        delete m_terrain;
        delete m_shader;
        delete m_pipeline;
    }

    void CRenderer::Init() {
        /// Clear color for framebuffer
        glClearColor(0.3f, 0.3f, 0.3f, 1.0);

        glEnable(GL_BLEND);                 /// Blending (transparent textures)
        glEnable(GL_CULL_FACE);             /// Cull facing (improve performance)
        glEnable(GL_DEPTH_TEST);            /// Depth test

        glCullFace(GL_BACK);
        glDepthFunc(GL_LEQUAL);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Pipeline().InitPipeline(45.0f, 4.0f/3.0f, 1.0f, 1500.0f);    /// fix init data if needed!

        Shader().LoadShader("assets/shaders/terrain.vs", "assets/shaders/terrain.fs");
        Terrain().Init();
    }

    void CRenderer::Render() {
        /*** Variables ***/
        static GLuint UID_MVP;

        /*** Implementation ***/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Camera().Update(CGame::Get().getDT());

        glUseProgram(Shader().GetID());
        UID_MVP = Shader().GetUniformID("MVP");
        Pipeline().MV().PushMatrix(Camera().getMatrix());

            glUniformMatrix4fv(UID_MVP, 1, GL_FALSE, &Pipeline().MVP()[0][0]);
            Terrain().Render();

        Pipeline().MV().PopMatrix();

    }

}
