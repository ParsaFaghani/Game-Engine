#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "core/InputManager.h"
#include "core/config/Config.h"
#include "core/config/EngineSettings.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

int main() {
    EngineSettings settings;
    Config conf(settings);
    // GLFW ? OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pro Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    InputManager::init(window);

    {
        Shader shader("../assets/shaders/vertex.glsl", "../assets/shaders/fragment.glsl");

        float cubeVertices[] = {
            // Position         // Normal
            -1,-1, 1,  0,0,1,   1,-1, 1,  0,0,1,   1, 1, 1,  0,0,1,
             1, 1, 1,  0,0,1,  -1, 1, 1,  0,0,1,  -1,-1, 1,  0,0,1,
            -1,-1,-1, 0,0,-1,  -1, 1,-1, 0,0,-1,   1, 1,-1, 0,0,-1,
             1, 1,-1, 0,0,-1,   1,-1,-1, 0,0,-1,  -1,-1,-1, 0,0,-1,
            -1, 1, 1, -1,0,0,  -1, 1,-1,-1,0,0,  -1,-1,-1,-1,0,0,
            -1,-1,-1,-1,0,0,  -1,-1, 1,-1,0,0,  -1, 1, 1,-1,0,0,
             1, 1, 1,  1,0,0,   1,-1,-1,1,0,0,   1, 1,-1,1,0,0,
             1,-1,-1,1,0,0,    1, 1, 1,1,0,0,    1,-1, 1,1,0,0,
            -1, 1,-1, 0,1,0,  -1, 1, 1,0,1,0,    1, 1, 1,0,1,0,
             1, 1, 1, 0,1,0,   1, 1,-1,0,1,0,  -1, 1,-1,0,1,0,
            -1,-1,-1, 0,-1,0,  1,-1,-1,0,-1,0,   1,-1, 1,0,-1,0,
             1,-1, 1,0,-1,0,  -1,-1, 1,0,-1,0,  -1,-1,-1,0,-1,0
        };

        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        Camera camera(glm::vec3(0, 0, 5), glm::vec3(0, 1, 0), -90.0f, 0.0f);
        float deltaTime = 0.0f, lastFrame = 0.0f;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        float degress = 5.0f;
        float lastTime = glfwGetTime();  // در ابتدای برنامه
        int nbFrames = 0;
        float fpsStartTime = 0.0f;

        while (!glfwWindowShouldClose(window)) {
            float currentTime = glfwGetTime();
            float deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            // FPS اندازه‌گیری
            nbFrames++;
            if (currentTime - fpsStartTime >= 1.0f) {
                std::cout << "FPS: " << nbFrames << std::endl;
                nbFrames = 0;
                fpsStartTime = currentTime;
            }




            InputManager::update();
            float sens = 0.2f;
            glm::vec2 mouseDelta = InputManager::getMouseDelta();
            // std::cout << "Mouse ?: " << mouseDelta.x*sens << ", " << mouseDelta.y*sens << "\n";
            camera.processMouseMovement(mouseDelta.x*sens, mouseDelta.y*sens);
            InputManager::setMouseDelta(glm::vec2(0.0f));

            if (InputManager::isKeyDown(GLFW_KEY_W)) camera.processKeyboard('W', deltaTime);
            if (InputManager::isKeyDown(GLFW_KEY_S)) camera.processKeyboard('S', deltaTime);
            if (InputManager::isKeyDown(GLFW_KEY_A)) camera.processKeyboard('A', deltaTime);
            if (InputManager::isKeyDown(GLFW_KEY_D)) camera.processKeyboard('D', deltaTime);

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                InputManager::setFirstMouse(true);
                glfwSetWindowShouldClose(window, true);
            }


            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.bind();
            glm::mat4 model = glm::mat4(1.0f);
            
            model = glm::rotate(model, glm::radians(degress), glm::vec3(0.0f,1.0f,0.0f));
       	    degress += 5.0f;
            shader.setMat4("model", model);
            shader.setMat4("view", camera.getViewMatrix());
            shader.setMat4("projection", glm::perspective(glm::radians(45.0f), 800.f/600.f, 0.1f, 100.f));
            shader.setVec3("lightPos", glm::vec3(2.0f, 4.0f, 1.5f));
            shader.setVec3("viewPos", camera.getPosition());
            shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
            shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}