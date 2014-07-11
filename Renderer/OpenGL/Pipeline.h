#ifndef PIPELINE_H_INCLUDED
#define PIPELINE_H_INCLUDED

#include <glm/glm.hpp>
#include "MatrixStack.h"

namespace OpenGL {

    class CPipeline {
        public:
            CPipeline();

            void            InitPipeline(float FoV = 45.0f, float aspect = 4.0f/3.0f, float near = 1.0f, float far = 100.0f);
            void            SetProjection(glm::mat4 pMatrix);
            void            ResetProjection();
            glm::mat4&      ProjectionMatrix();
            glm::mat4&      ModelviewMatrix();
            glm::mat4       MVP();
            CMatrixStack&   MV();

        private:
            /*** Variables ***/
            float           m_fov;
            float           m_aspect;
            float           m_near;
            float           m_far;

            glm::mat4       m_projection;   //Projection matrix
            CMatrixStack    m_modelview;    //Model-view matrix
    };

}

#endif // PIPELINE_H_INCLUDED
