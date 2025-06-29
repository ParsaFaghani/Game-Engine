#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>

class InputManager {
public:
    static void init(GLFWwindow* window);
    static void update();

    static bool isKeyDown(int key);
    static bool isKeyPressed(int key);
    static bool isKeyReleased(int key);
    static glm::vec2 getMouseDelta();
    static void setFirstMouse(bool val);

private:
    static GLFWwindow* s_window;
    static std::unordered_map<int, bool> s_currentKeys;
    static std::unordered_map<int, bool> s_previousKeys;
    static glm::vec2 s_lastMousePos;
    static glm::vec2 s_mouseDelta;
    static bool s_firstMouse;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
};