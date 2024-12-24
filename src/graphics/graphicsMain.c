#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders/shaders.h"

void cleanupGLFW(GLFWwindow* window);
GLFWwindow* setup(int width, int height, char* windowName, GLFWmonitor* fullscreenMonitor);

int main(void) {

    GLFWwindow* window = setup(1000, 1000, "PhysEngineTest", NULL);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    cleanupGLFW(window);
    return 0;
}



//Fullscreen monitor can be null for a windowed application
GLFWwindow* setup(int width, int height, char* windowName, GLFWmonitor* fullscreenMonitor) {
    //Starts GLFW (Creates window)
    glfwInit();

    //Passing OpenGL contexts to glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Using OpenGL Core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Window creation
    //2nd to last Null is fullscreen
    GLFWwindow* window = glfwCreateWindow(width, height, windowName, fullscreenMonitor, NULL);
    //Error checking
    if (window == NULL) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    //Starting glad things
    gladLoadGL();
    glViewport(0, 0, width, height);

    //Make this user editable?
    glClearColor(0.0f,0.0f,0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint fragmentShader = createFragmentShader(fragmentSourceString);
    GLuint vertexShader = createVertexShader(vertexSourceString);

    GLuint shaderProgram = glCreateProgram();
    //Creating the shader program and attaching the shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //Cleaning up the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Returning the window
    return window;
}

void cleanupGLFW(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}
