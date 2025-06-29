#include "InputManager.h"

GLFWwindow* InputManager::s_window = nullptr;
std::unordered_map<int, bool> InputManager::s_currentKeys;
std::unordered_map<int, bool> InputManager::s_previousKeys;
glm::vec2 InputManager::s_lastMousePos(0.0f);
glm::vec2 InputManager::s_mouseDelta(0.0f);
bool InputManager::s_firstMouse = true;

void InputManager::init(GLFWwindow* window) {
    s_window = window;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputManager::update() {
    s_previousKeys = s_currentKeys;
    s_mouseDelta = glm::vec2(0.0f); // reset after use
}

bool InputManager::isKeyDown(int key) {
    return s_currentKeys[key];
}

bool InputManager::isKeyPressed(int key) {
    return s_currentKeys[key] && !s_previousKeys[key];
}

bool InputManager::isKeyReleased(int key) {
    return !s_currentKeys[key] && s_previousKeys[key];
}

glm::vec2 InputManager::getMouseDelta() {
    return s_mouseDelta;
}

void InputManager::setFirstMouse(bool val) {
    s_firstMouse = val;
}

void InputManager::keyCallback(GLFWwindow* window, int key, int, int action, int) {
    if (action == GLFW_PRESS)
        s_currentKeys[key] = true;
    else if (action == GLFW_RELEASE)
        s_currentKeys[key] = false;
}

void InputManager::mouseCallback(GLFWwindow*, double xpos, double ypos) {
    if (s_firstMouse) {
        s_lastMousePos = glm::vec2(xpos, ypos);
        s_firstMouse = false;
        return;
    }

    glm::vec2 current(xpos, ypos);
    s_mouseDelta = current - s_lastMousePos;
    s_lastMousePos = current;
}