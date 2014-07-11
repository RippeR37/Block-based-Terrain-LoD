#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <gl/glew.h>

#include "Types.h"
#include "Terrain.h"
#include "FreeCamera.h"
#include "OpenGL/Pipeline.h"
#include "OpenGL/Shader.h"

namespace Rendering {

    class CRenderer {
        public:
            CRenderer();
            ~CRenderer();

            void Init();
            void Render();

            CTerrain& Terrain()             { return *m_terrain; }
            CFreeCamera& Camera()           { return *m_camera; }
            OpenGL::CPipeline& Pipeline()   { return *m_pipeline; }
            OpenGL::CShader& Shader()       { return *m_shader; }

        private:
            CTerrain*               m_terrain;
            CFreeCamera*            m_camera;

            OpenGL::CShader*        m_shader;
            OpenGL::CPipeline*      m_pipeline;
    };

}

#endif // RENDERER_H_INCLUDED
