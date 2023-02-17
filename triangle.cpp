#pragma clang diagnostic push
#pragma clang diagnostic ignored "-WDocumentation"
#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;

#define numVAOs 1

GLuint  renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() {
    // vertex shader
    const char *vshaderSource =
            "#version 410 \n"
            "uniform float offset; \n"
            "void main(void) \n"
            "{ if (gl_VertexID == 0) gl_Position = vec4(0.25 + offset, -0.25, 0.0, 1.0);"
            "else if (gl_VertexID == 1) gl_Position = vec4(-0.25 + offset, -0.25, 0.0, 1.0);"
            "else gl_Position = vec4(0.25 + offset, 0.25, 0.0, 1.0);"
            "}";

    // fragment shader
    const char *fshaderSource =
            "#version 410 \n"
            "out vec4 color; \n"
            "void main(void) \n"
            "{ if(gl_FragCoord.x < 295) color = vec4(0.1, 0.01, 0.5, 0.5);"
            "else color = vec4(0.1, 0.3, 0.4, 0.2); }";
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, nullptr);
    glShaderSource(fShader, 1, &fshaderSource, nullptr);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

float x = 0.0f;
float inc = 0.01f;

void display(GLFWwindow* window, double currentTime) {
    // background
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1, 0.2, 0.3, .01);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    x += inc;
    if (x > 1.0f) inc = -0.01f;
    if (x < -1.0f) inc = 0.01f;
    GLint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLoc, x);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    if (!glfwInit()) { exit(EXIT_FAILURE); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "randy", nullptr, nullptr);
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
