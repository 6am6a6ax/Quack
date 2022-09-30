#include <iostream>

#include "quack/core/application.h"

#include "quack/platform/glfw/window_glfw.h"
#include "quack/platform/opengl/gpu_device_opengl.h"
#include "quack/platform/opengl/gpu_context_opengl.h"

int main() {
    Quack::WindowDescription wndDesc;
    wndDesc.WindowSize = { 1280, 720 };
    wndDesc.Title = "Quack Model Loader";

    Quack::ApplicationDescription appDesc;
    appDesc.GPUDevice = new Quack::GPUDeviceOpenGL;
    appDesc.Scene = new Quack::Scene;
    appDesc.Window = new Quack::WindowGLFW(wndDesc);

    Quack::Application::GetInstance().Init(appDesc);
    Quack::Application::GetInstance().Run();

    return 0;
}