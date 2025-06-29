#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    glm::mat4 getViewMatrix() const;
    void processKeyboard(char direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

private:
    void updateCameraVectors();

    glm::vec3 m_position, m_front, m_up, m_right, m_worldUp;
    float m_yaw, m_pitch;
    float m_speed = 2.5f;
    float m_sensitivity = 0.08f;
};