#include <quack/quack.h>

#include <quack-model-loader/layers/layer_test.h>

int main() {
    Quack::WindowDescription wndDesc;
    wndDesc.WindowSize = { 1280, 720 };
    wndDesc.Title = "Quack Model Loader";

    Quack::ApplicationDescription appDesc;
    appDesc.GPUDevice = std::make_shared<Quack::GPUDeviceOpenGL>();
    appDesc.Scene = std::make_shared<Quack::Scene>();
    appDesc.Window = std::make_shared<Quack::WindowGLFW>(wndDesc);

    Quack::Application::GetInstance().Init(appDesc);
    Quack::Application::GetInstance().GetLayerStack()->Push(std::make_shared<ModelLoader::LayerTest>("test"));
    Quack::Application::GetInstance().Run();

    return 0;
}