#include <iostream>

#include "platform/opengl/gpu_buffer_opengl.hpp"

//int main() {
//    std::cout << "Hello, World!\n";
//
//    Quack::GPUBufferDescription description;
//    description.Size = 1;
//    description.Stride = 2;
//    description.Usage = Quack::GPUResourceUsage::Default;
//    description.Format = Quack::GPUPixelFormat::Unknown;
//    description.Utility = Quack::GPUBufferUtility::Unknown;
//
//    Quack::GPUBufferOpenGL buffer = Quack::GPUBufferOpenGL(description);
//
//    buffer.Bind();
//
//    return 0;
//}


#include <GL/glew.h>



#include "core/application.hpp"

#include <GLFW/glfw3.h>



class Application : public Quack::Application {
public:
    static void Init() {
        std::cout << "Hello, World!\n";

        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void Exit() {}
};

int main() {
    glfwInit();

    GLFWwindow * window = glfwCreateWindow(640, 480, "Test", 0, 0);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}