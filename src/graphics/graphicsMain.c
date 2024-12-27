#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "shaders/shaders.h"



//Vertecies for testing purposes
typedef struct {
    GLfloat* points;
    int size;
    int num;
} VertexArray;

//Return type for the shader initialization
struct GLThings {
   GLuint shader;
   GLuint VAO;
   GLuint VBO;
};



void cleanupGLFW(GLFWwindow* window, struct GLThings gl);
GLFWwindow* setup(int width, int height, char* windowName, GLFWmonitor* fullscreenMonitor);
GLuint createFragmentShader(const GLchar* sourceString);
GLuint createVertexShader(const GLchar* sourceString);
struct GLThings initializeShaders();




GLfloat pointArr[] = {
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.0f, 0.0f, 0.0f
};

VertexArray vertecies = {pointArr, sizeof(pointArr), 3};

//Testing loop currently
int main(void) {
    //Not sure if this comes with the shaders as well
    GLFWwindow* window = setup(1000, 1000, "PhysEngineTest", NULL);
    struct GLThings graphicsStuff = initializeShaders();
    


    //Main loop (Will eventually be in a seperate file)
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(graphicsStuff.shader);
        glBindVertexArray(graphicsStuff.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }

    cleanupGLFW(window, graphicsStuff);
    return 0;
}

struct GLThings initializeShaders() {
    struct GLThings output;

    //Make this user editable?
    glClearColor(0.0f,0.0f,0.0f, 1.0f);

    GLuint fragmentShader = createFragmentShader(fragmentSourceString);
    GLuint vertexShader = createVertexShader(vertexSourceString);

    output.shader = glCreateProgram();
    //Creating the shader program and attaching the shaders
    glAttachShader(output.shader, vertexShader);
    glAttachShader(output.shader, fragmentShader);
    glLinkProgram(output.shader);
    
    //Cleaning up the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Buffer setups... Probably should figure out how to abstract this better in the future
    glGenVertexArrays(1, &output.VAO);
    glGenBuffers(1, &output.VBO);

    glBindVertexArray(output.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, output.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertecies.size, vertecies.points, GL_STATIC_DRAW);

    //Starting position, number of vertecies, type, something, stride, something else
    glVertexAttribPointer(0, vertecies.num, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Binding to zero to prevent shenanigans
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return output;
}

//Fullscreen monitor can be null for a windowed application
//Returns a configured window with attached shaders (I think?)
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
    //The one openGL function that gets to stay... Hopefully that won't explode everything
    glViewport(0, 0, width, height);

    glfwMakeContextCurrent(window);
    //Starting glad things
    gladLoadGL();

    //Returning the window
    return window;
}

void cleanupGLFW(GLFWwindow* window, struct GLThings gl) {
    glDeleteBuffers(1, &gl.VBO);
    glDeleteVertexArrays(1, &gl.VAO);
    glDeleteProgram(gl.shader);
    glfwDestroyWindow(window);
    glfwTerminate();
}



//Creates a vertex shader based on a source string
GLuint createVertexShader(const GLchar* sourceString) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &sourceString, NULL);
    glCompileShader(vertexShader);

    return vertexShader;
}


//Creates a fragment shader based on a source string
GLuint createFragmentShader(const GLchar* sourceString) {
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &sourceString, NULL);
    glCompileShader(fragmentShader);

    return fragmentShader;
}
