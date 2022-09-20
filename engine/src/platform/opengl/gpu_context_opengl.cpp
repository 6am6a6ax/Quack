#include <GL/glew.h>

#include "quack/platform/opengl/gpu_context_opengl.h"

Quack::GPUContextOpenGL::GPUContextOpenGL(GLFWwindow * handle) : _handle(handle) {}

void Quack::GPUContextOpenGL::Init() {
    glfwMakeContextCurrent(_handle);
    glewInit();
}

void Quack::GPUContextOpenGL::SwapBuffers() {
    glfwSwapBuffers(_handle);
}
