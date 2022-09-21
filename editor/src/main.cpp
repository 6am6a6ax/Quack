#include "quack/core/application.h"

#include "quack/platform/glfw/window_glfw.h"
#include "quack/platform/opengl/gpu_device_opengl.h"

int main() {
    Quack::WindowDescription windowDesc;
    windowDesc.WindowSize = {1280, 720};
    windowDesc.Title = "Quack Editor";

    Quack::ApplicationDescription appDesc;
    appDesc.Window = new Quack::WindowGLFW(windowDesc);
    appDesc.GPUDevice = new Quack::GPUDeviceOpenGL();

    Quack::Application::GetInstance().Init(appDesc);
    Quack::Application::GetInstance().Run();

    return 0;
}