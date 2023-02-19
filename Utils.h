//
// Created by Randy Hartzell on 17 Feb 2023.
//

#ifndef GRAPHICS3_UTILS_H
#define GRAPHICS3_UTILS_H

using namespace std;

namespace utils {

    class Utils {


    public:
        static void glfwError(int id, const char* description);

        static string readShaderSource(const char *filePath);

        static void printShaderLog(GLuint shader);

        static void printProgramLog(int prog);

        static bool checkOpenGLError();
    };

} // utils

static glm::mat4 buildTranslate(float x, float y, float z);

static glm::mat4 buildScale(float x, float y, float z);

static glm::mat4 rotateX(float rad);

static glm::mat4 rotateY(float rad);

static glm::mat4 rotateZ(float rad);

#endif //GRAPHICS3_UTILS_H
