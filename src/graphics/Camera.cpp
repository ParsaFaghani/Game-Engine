#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    : m_position(pos), m_worldUp(up), m_yaw(yaw), m_pitch(pitch) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(char dir, float dt) {
    float v = m_speed * dt;
    if (dir == 'W') m_position += m_front * v;
    if (dir == 'S') m_position -= m_front * v;
    if (dir == 'A') m_position -= m_right * v;
    if (dir == 'D') m_position += m_right * v;
}

void Camera::processMouseMovement(float x, float y, bool constrainPitch) {
    x *= m_sensitivity;
    y *= m_sensitivity;

    m_yaw += x;
    m_pitch -= y;

    if (constrainPitch) {
        if (m_pitch > 89.0f)  m_pitch = 89.0f;
        if (m_pitch < -89.0f) m_pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}