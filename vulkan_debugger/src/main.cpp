#include "GLFW/glfw3.h"
#include <quack/quack.h>

int main() {
    Quack::WindowDescription windowDesc{};
    windowDesc.WindowSize = { 1280, 720 };
    windowDesc.Title = "Vulkan Debugger";

    Quack::Window* window = new Quack::WindowGLFW(windowDesc);

    Quack::GPUContext::Desciption gpuContextDesc{};
    Quack::GPUContext* gpuContext = new Quack::GPUContextVulkan();

    Quack::ApplicationDescription appDesc{};
    appDesc.Window = window;
    appDesc.GPUContext = gpuContext;
    // // appDesc.GPUDevice = new Quack::GPUDeviceVulkan();
    // // appDesc.Camera = new Quack::CameraPerspective();

    Quack::Application::GetInstance().Init(appDesc);

    try {
        Quack::Application::GetInstance().Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}