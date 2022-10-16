#include "quack/core/window.h"
#include "quack/quack.h"

// Quack::GPUContextOpenGL::GPUContextOpenGL(const Quack::GPUContext::Desciption& desc) 
//     : Quack::GPUContext(desc) {}

void Quack::GPUContextOpenGL::Init() {
    glfwMakeContextCurrent((GLFWwindow*)Application::GetInstance().GetWindow()->GetHandle());
    glewInit();
}

void Quack::GPUContextOpenGL::SwapBuffers() {
    glfwSwapBuffers((GLFWwindow*)Application::GetInstance().GetWindow()->GetHandle());
}
