#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "MatrixStack.h"
#include <glm/gtc/matrix_transform.hpp>

namespace OpenGL {

    CMatrixStack::CMatrixStack() {
        m_id = glm::mat4(1.0f);
        m_stack.push(m_id);
    }

    void CMatrixStack::LoadID() {
        m_stack.top() = m_id;
    }

    void CMatrixStack::LoadMatrix(glm::mat4& matrix) {
        m_stack.top() = matrix;
    }

    void CMatrixStack::MultiplyMatrix(glm::mat4& matrix) {
        m_stack.top() *= matrix;
    }

    void CMatrixStack::PopMatrix() {
        m_stack.pop();
    }

    void CMatrixStack::PushMatrix() {
        m_stack.push(m_stack.top());
    }

    void CMatrixStack::PushMatrix(glm::mat4& matrix) {
        m_stack.push(matrix);
    }

    void CMatrixStack::Rotate(float angle, float x, float y, float z) {
        m_stack.top() = glm::rotate(m_stack.top(), angle, glm::vec3(x, y, z));
    }

    void CMatrixStack::Translate(float x, float y, float z) {
        m_stack.top() = glm::translate(m_stack.top(), glm::vec3(x, y, z));
    }

    void CMatrixStack::Scale(float x, float y, float z) {
        m_stack.top() = glm::scale(m_stack.top(), glm::vec3(x, y, z));
    }

    glm::mat4& CMatrixStack::GetMatrix() {
        return m_stack.top();
    }

}
