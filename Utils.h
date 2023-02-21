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

        static GLuint loadTexture(const char *textImagePath);
    };

} // utils
#endif //GRAPHICS3_UTILS_H
