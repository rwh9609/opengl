//
// Created by Randy Hartzell on 17 Feb 2023.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-WDocumentation"
#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Utils.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace utils;

#define numVAOs 1
#define numVBOs 2

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint  renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// allocate variables used in display() function, so that they won't need to be allocated during rendering
GLuint mvLoc, projLoc, vLoc, tfLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;

void setupVertices() { // 36 vertices, 12 triangles, makes 2x2x2 cube placed at origin
    float vertexPositions[108] = {
            -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
            -1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,
            1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,-1.0f
    };
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

GLuint createShaderProgram() {
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    string vertShaderString = Utils::readShaderSource("/Users/randyhartzell/CLionProjects/graphics/CubeInstancingVertShader.glsl");
    string fragShaderString = Utils::readShaderSource("/Users/randyhartzell/CLionProjects/graphics/CubeInstancingFragShader.glsl");
    const char *vertShaderSrc = vertShaderString.c_str();
    const char *fragShaderSrc = fragShaderString.c_str();

    glShaderSource(vShader, 1, &vertShaderSrc, nullptr);
    glShaderSource(fShader, 1, &fragShaderSrc, nullptr);

    // vertex shader compilation
    glCompileShader(vShader);
    Utils::checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        cout << "vertex compilation failed" << endl;
        Utils::printShaderLog(vShader);
    }

    // fragment shader compilation
    glCompileShader(fShader);
    Utils::checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
        cout << "frag compilation failed" << endl;
        Utils::printShaderLog(fShader);
    }

    // program creation
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    Utils::checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "linking failed" << endl;
        Utils::printProgramLog(vfProgram);
    }
    return vfProgram;
}

void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 25.0f;
    cubeLocX = 0.0f; cubeLocY = 0.0f; cubeLocZ = 0.0f; // shift down Y to reveal perspective;
    setupVertices();
}

void display(GLFWwindow* window, double currentTime) {
    // background
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);

    // get the uniform variables for the matrices
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    vLoc = glGetUniformLocation(renderingProgram, "v_matrix");

    // build perspective matrix
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float) width/ (float) height;
    pMat = glm::perspective(1.4472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    // build view matrix
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    float timeFactor;
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));

    timeFactor = ((float)currentTime);
    tfLoc = glGetUniformLocation(renderingProgram, "tf");
    glUniform1f(tfLoc, (float)timeFactor);

    // copy perspective and MV matrices to corresponding uniform variables
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

    // associate VBO with the corresponding vertex attribute in the vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // adjust OpenGL settings and draw model
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100000);
}

int main() {
    glfwSetErrorCallback(&Utils::glfwError);
    if (!glfwInit()) { exit(EXIT_FAILURE); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1400, 800, "randy", nullptr, nullptr);
    int actualScreenWidth, actualScreenHeight;
    glfwGetFramebufferSize(window, &actualScreenWidth, &actualScreenHeight);
    glfwMakeContextCurrent(window);
    glViewport(0,0,actualScreenWidth,actualScreenHeight);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
