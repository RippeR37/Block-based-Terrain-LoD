#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "Pipeline.h"
#include <glm/gtc/matrix_transform.hpp>

namespace OpenGL {

    CPipeline::CPipeline() {

    }

    void CPipeline::InitPipeline(float FoV, float aspect, float near, float far) {
        m_fov    = FoV;
        m_aspect = aspect;
        m_near   = near;
        m_far    = far;

        ResetProjection();
    }

    void CPipeline::SetProjection(glm::mat4 pMatrix) {
        m_projection = pMatrix;
    }

    void CPipeline::ResetProjection() {
        m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
    }

    glm::mat4& CPipeline::ProjectionMatrix() {
        return m_projection;
    }

    glm::mat4& CPipeline::ModelviewMatrix() {
        return m_modelview.GetMatrix();
    }

    glm::mat4 CPipeline::MVP() {
        return m_projection * m_modelview.GetMatrix();
    }

    CMatrixStack& CPipeline::MV() {
        return m_modelview;
    }

}
