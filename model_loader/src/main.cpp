#include <quack/quack.h>

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