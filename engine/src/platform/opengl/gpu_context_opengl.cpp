#include "quack/quack.h"

Quack::GPUContextOpenGL::GPUContextOpenGL(GLFWwindow * handle) : _handle(handle) {}

void Quack::GPUContextOpenGL::Init() {
    glfwMakeContextCurrent(_handle);
    glewInit();
}

void Quack::GPUContextOpenGL::SwapBuffers() {
    glfwSwapBuffers(_handle);
}
