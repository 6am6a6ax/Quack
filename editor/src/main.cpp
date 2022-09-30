//#include "quack/core/application.h"
//#include "quack/platform/glfw/window_glfw.h"
//#include "quack/platform/opengl/gpu_device_opengl.h"

#include <quack/quack.h>

#include "quack-editor/layers/layer_quad.h"
#include "quack-editor/layers/layer_triangle.h"
#include "quack-editor/layers/layer_hierarchy_panel.h"
#include "quack-editor/layers/layer_components.h"
#include "quack-editor/scene_editor.h"

int main() {
    Quack::WindowDescription windowDesc;
    windowDesc.WindowSize = {1280, 720};
    windowDesc.Title = "Quack Editor";

    Quack::ApplicationDescription appDesc;
    appDesc.Window = new Quack::WindowGLFW(windowDesc);
    appDesc.GPUDevice = new Quack::GPUDeviceOpenGL();
    appDesc.Scene = new Quack::Scene;

    auto * scene = (Quack::SceneEditor *)appDesc.Scene;

    Quack::Application::GetInstance().Init(appDesc);
    Quack::Application::GetInstance().GetLayerStack().Push(std::make_shared<Quack::LayerQuad>("Quad", scene));
    //Quack::Application::GetInstance().GetLayerStack().Push(std::make_shared<Quack::LayerTriangle>("Triangle"));
    Quack::Application::GetInstance().GetLayerStack().Push(std::make_shared<Quack::LayerHierarchyPanel>("Scene Hierarchy Panel", scene));
    Quack::Application::GetInstance().GetLayerStack().Push(std::make_shared<Quack::LayerComponents>(scene));
    Quack::Application::GetInstance().Run();

    return 0;
}
