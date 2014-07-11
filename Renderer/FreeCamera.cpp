#include "FreeCamera.h"
#include "../Game.h"

#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <cmath>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace Rendering {

    CFreeCamera::CFreeCamera() {
        m_position = glm::vec3( 0.0f, 30.0f, 0.0f );

        m_angle_x = 0.9f;
        m_angle_y = 0.0f;

        m_speed = 5.0f;
        m_mouse_speed = 0.003f;
    }

    CFreeCamera::~CFreeCamera() {

    }

    void CFreeCamera::Update(double dt) {
        /*** Variables  ***/
        static glm::vec3 direction;
        static glm::vec3 right;
        static glm::vec3 up;
        static float speed;

        direction = glm::vec3((float)(cos(m_angle_y) * sin(m_angle_x)), (float)sin(m_angle_y), (float)(cos(m_angle_y) * cos(m_angle_x)));
        right     = glm::vec3(sin(m_angle_x - 3.14f/2.0f), 0, cos(m_angle_x - 3.14f/2.0f));
        up        = glm::cross( right, direction );

        dt = CGame::Get().getDT();
        if(glfwGetKey(CGame::Get().Window().GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            speed = m_speed * dt * 10;
        } else {
            speed = m_speed * dt;
        }

        if(glfwGetKey(CGame::Get().Window().GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            m_position -= right * speed;
        } else if(glfwGetKey(CGame::Get().Window().GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            m_position += right * speed;
        }

        if(glfwGetKey(CGame::Get().Window().GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
            m_position += up * speed;
        } else if(glfwGetKey(CGame::Get().Window().GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            m_position -= up * speed;
        }

        if(glfwGetKey(CGame::Get().Window().GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            m_position += direction * speed;
        } else if(glfwGetKey(CGame::Get().Window().GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            m_position -= direction * speed;
        }

        m_matrix = glm::lookAt(m_position, m_position+direction, up);
    }

    void CFreeCamera::UpdateMouse(int x, int y) {
        m_angle_x -= x * m_mouse_speed; // * CGame::Get().getDT();
        m_angle_y -= y * m_mouse_speed; //* CGame::Get().getDT();
    }

}
