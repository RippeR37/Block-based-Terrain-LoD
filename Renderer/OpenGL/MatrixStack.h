#ifndef MATRIXSTACK_H_INCLUDED
#define MATRIXSTACK_H_INCLUDED

#include <stack>
#include <glm/glm.hpp>

namespace OpenGL {

    class CMatrixStack {
        public:
            CMatrixStack();

            void LoadID();
            void LoadMatrix(glm::mat4& matrix);
            void MultiplyMatrix(glm::mat4& matrix);
            void PopMatrix();
            void PushMatrix();
            void PushMatrix(glm::mat4& matrix);

            void Rotate(float angle, float x, float y, float z);
            void Translate(float x, float y, float z);
            void Scale(float x, float y, float z);

            glm::mat4& GetMatrix();


        private:
            glm::mat4               m_id;
            std::stack<glm::mat4>   m_stack;
    };

}

#endif // MATRIXSTACK_H_INCLUDED
