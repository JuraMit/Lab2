#define GLEW_DLL
#define GLFW_DLL

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include <iostream>
#include "shader.h"

GLfloat points[] = {
    0.0f, 1.0f, 0.0f,
    -0.951f, 0.309f, 0.0f,
    -0.588f, -0.809f, 0.0f,
    0.588f, -0.809f, 0.0f,
    0.951f, 0.309f, 0.0f
};

GLuint index[] = { 0, 1, 2, 3, 4 };

int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    GLFWwindow* window = glfwCreateWindow(512, 512, "PENTAGON", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

    while (!glfwWindowShouldClose(window)) {
        float timeValue = glfwGetTime();

        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        shader.setUniform("ourColor", abs(cos(timeValue)), abs(sin(timeValue)), abs(cos(timeValue) - 0.5f), 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}