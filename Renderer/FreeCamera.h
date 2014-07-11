#ifndef FREECAMERA_H_INCLUDED
#define FREECAMERA_H_INCLUDED

#include <glm/glm.hpp>

namespace Rendering {

    class CFreeCamera {
        public:
            CFreeCamera();
            ~CFreeCamera();

            void Update(double dt);
            void UpdateMouse(int x, int y);

            glm::vec2  getPos2D()   { return glm::vec2(m_position[0], m_position[2]); }
            glm::mat4& getMatrix()  { return m_matrix; }

        private:
            float m_speed;
            float m_angle_x;
            float m_angle_y;
            float m_mouse_speed;

            glm::vec3   m_position;
            glm::mat4   m_matrix;
    };

}

#endif // FREECAMERA_H_INCLUDED
