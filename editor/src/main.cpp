#include <iostream>

#include "quack/core/application.h"

#include "quack/platform/opengl/gpu_device_opengl.h"

int main() {
    std::cout << "Hello, World! Starting...\n";

    Quack::ApplicationDescription appDesc;
    appDesc.SetDevice(new Quack::GPUDeviceOpenGL());

    Quack::Application::GetInstance().SetDescription(appDesc);

    Quack::WindowDescription windowDesc;
    windowDesc.SetSize({1280, 720});
    windowDesc.SetTitle("Quack Editor");
    Quack::Application::GetInstance().Init(windowDesc);

    Quack::Application::GetInstance().Run();

    return 0;
}