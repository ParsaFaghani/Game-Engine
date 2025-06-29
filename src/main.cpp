 #include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "core/InputManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Pro Camera", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 800, 600);

    InputManager::init(window);
    Shader shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");



float cubeVertices[] = {
    // ??????        // ?????

    // ? ??? ??? (z = +1)
    -1, -1,  1,     0,  0,  1,
     1, -1,  1,     0,  0,  1,
     1,  1,  1,     0,  0,  1,
     1,  1,  1,     0,  0,  1,
    -1,  1,  1,     0,  0,  1,
    -1, -1,  1,     0,  0,  1,

    // ? ??? ??? (z = -1)
    -1, -1, -1,     0,  0, -1,
    -1,  1, -1,     0,  0, -1,
     1,  1, -1,     0,  0, -1,
     1,  1, -1,     0,  0, -1,
     1, -1, -1,     0,  0, -1,
    -1, -1, -1,     0,  0, -1,

    // ? ??? ?? (x = -1)
    -1,  1,  1,    -1,  0,  0,
    -1,  1, -1,    -1,  0,  0,
    -1, -1, -1,    -1,  0,  0,
    -1, -1, -1,    -1,  0,  0,
    -1, -1,  1,    -1,  0,  0,
    -1,  1,  1,    -1,  0,  0,

    // ? ??? ???? (x = +1)
     1,  1,  1,     1,  0,  0,
     1, -1, -1,     1,  0,  0,
     1,  1, -1,     1,  0,  0,
     1, -1, -1,     1,  0,  0,
     1,  1,  1,     1,  0,  0,
     1, -1,  1,     1,  0,  0,

    // ? ??? ???? (y = +1)
    -1,  1, -1,     0,  1,  0,
    -1,  1,  1,     0,  1,  0,
     1,  1,  1,     0,  1,  0,
     1,  1,  1,     0,  1,  0,
     1,  1, -1,     0,  1,  0,
    -1,  1, -1,     0,  1,  0,

    // ? ??? ????? (y = -1)
    -1, -1, -1,     0, -1,  0,
     1, -1, -1,     0, -1,  0,
     1, -1,  1,     0, -1,  0,
     1, -1,  1,     0, -1,  0,
    -1, -1,  1,     0, -1,  0,
    -1, -1, -1,     0, -1,  0
};
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
{
    Camera camera(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0), -90, 0);
    float deltaTime = 0, lastFrame = 0;

    while (!glfwWindowShouldClose(window)) {
        float now = glfwGetTime();
        deltaTime = now - lastFrame;
        lastFrame = now;

        InputManager::update();

        glm::vec2 mouse = InputManager::getMouseDelta();
        camera.processMouseMovement(mouse.x, mouse.y);

        if (InputManager::isKeyDown(GLFW_KEY_W)) camera.processKeyboard('W', deltaTime);
        if (InputManager::isKeyDown(GLFW_KEY_S)) camera.processKeyboard('S', deltaTime);
        if (InputManager::isKeyDown(GLFW_KEY_A)) camera.processKeyboard('A', deltaTime);
        if (InputManager::isKeyDown(GLFW_KEY_D)) camera.processKeyboard('D', deltaTime);


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // ??? ?? ???? ??
	    glfwSetWindowShouldClose(window, true);                      // ?????? ?? ????
	}

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        shader.setMat4("uModel", glm::mat4(1.0f));
        shader.setMat4("uView", camera.getViewMatrix());
        shader.setMat4("uProjection", glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.f));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
}