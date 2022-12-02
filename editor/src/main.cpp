#include <quack/quack.h>

#include "quack-editor/layers/layer_quad.h"
#include "quack-editor/camera.h"

int main() {
    Quack::WindowDescription windowDesc;
    windowDesc.WindowSize = { 1280, 720 };
    windowDesc.Title = "Quack Editor";

    Quack::ApplicationDescription appDesc;
    appDesc.Window = std::make_shared<Quack::WindowGLFW>(windowDesc);
    appDesc.GPUDevice = std::make_shared<Quack::GPUDeviceOpenGL>();
    //appDesc.Camera = new Quack::OrtographicCamera(-10.0f, 10.0f, -10.0f, 10.0f);
    appDesc.Camera = std::make_shared<Quack::Editor::CameraEditor>();
    appDesc.LayerStack = std::make_shared<Quack::LayerStack>();

    Quack::Application::GetInstance().Init(appDesc);
    Quack::Application::GetInstance().GetLayerStack()->Push(std::make_shared<Quack::Editor::LayerQuad>("View 1"));
    Quack::Application::GetInstance().Run();

    return 0;
}
