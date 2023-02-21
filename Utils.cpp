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
#include <SOIL2/soil2.h>
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

GLuint Utils::loadTexture(const char *textImagePath) {
    GLuint textureID;
    textureID = SOIL_load_OGL_texture(textImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID == 0) cout << "could not find texture file" << textImagePath << endl;
    return textureID;
}
