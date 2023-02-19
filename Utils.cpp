//
// Created by Randy Hartzell on 17 Feb 2023.
//

#include <string>
#include <iostream>
#include <fstream>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-WDocumentation"
#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

using namespace utils;

void Utils::glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

string Utils::readShaderSource(const char *filePath) {
    ifstream fl(filePath);
    if (!fl.is_open()) {
        std::cout << std::filesystem::current_path().string() << std::endl;
        cout << "failed to open file: " << filePath << std::endl;
        return "";
    }
    string content;
    std::cout << "readShaderSource ... filePath: " << filePath << std::endl;
    ifstream fileStream(filePath, ios::in);
    string line;
    while (!fileStream.eof()) {
        getline(fileStream, line);
        std::cout << "getLine" << line << " endLine" << endl;
        content.append(line + "\n");
    }
    fileStream.close();
    std::cout << "readShaderSource end ..." << std::endl;
    return content;
}

void Utils::printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if(len>0) {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader info log: " << log << endl;
        free(log);
    }

}

void Utils::printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if(len>0) {
        log = (char *)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        cout << "Program info log: " << log << endl;
        free(log);
    }

}

bool Utils::checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

glm::mat4 buildTranslate(float x, float y, float z) {
    glm::mat4 trans = glm::mat4(1.0, 0.0, 0.0, 0.0,
                                0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, 1.0, 0.0,
                                x, y, z, 1.0 );
    return trans;
}

glm::mat4 buildScale(float x, float y, float z) {
    glm::mat4 scale = glm::mat4(x, 0.0, 0.0, 0.0,
                                0.0, y, 0.0, 0.0,
                                0.0, 0.0, z, 0.0,
                                0.0, 0.0, 0.0, 1.0 );
    return scale;
}

glm::mat4 rotateX(float rad) {
    glm::mat4 xrot = glm::mat4(1.0, 0.0, 0.0, 0.0,
                               0.0, cos(rad), -sin(rad), 0.0,
                               0.0, sin(rad), cos(rad), 0.0,
                               0.0, 0.0, 0.0, 1.0 );
    return xrot;
}

glm::mat4 rotateY(float rad) {
    glm::mat4 yrot = glm::mat4(cos(rad), 0.0, sin(rad), 0.0,
                               0.0, 1.0, 0.0, 0.0,
                               -sin(rad), 0.0, cos(rad), 0.0,
                               0.0, 0.0, 0.0, 1.0 );
    return yrot;
}

glm::mat4 rotateZ(float rad) {
    glm::mat4 zrot = glm::mat4(cos(rad), -sin(rad), 0.0, 0.0,
                               sin(rad), cos(rad), 0.0, 0.0,
                               0.0, 0.0, 1.0, 0.0,
                               0.0, 0.0, 0.0, 1.0 );
    return zrot;
}
