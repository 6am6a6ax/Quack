#include "quack/core/asset_library.h"
#include "quack/quack.h"

Quack::Application & Quack::Application::GetInstance() {
    static Application application;
    return application;
}

void Quack::Application::Init(const Quack::ApplicationDescription & desc) {
    SetDescription(desc);
    BindBaseCallbackAndLayerStack();
    _desc.AssetLibrary = AssetLibrary();
}

void Quack::Application::Run() {
    while (true) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        //ImGuizmo::BeginFrame();

        OnUpdate();

        Quack::ApplicationUpdated e;
        OnEvent(e);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void Quack::Application::OnEvent(Quack::Event & e) {
    GetWindow()->OnEvent(e);
    for (const auto & layer : GetLayerStack()) {
        layer->OnEvent(e);
    }
}

const Quack::ApplicationDescription & Quack::Application::GetDescription() {
    return _desc;
}

void Quack::Application::BindBaseCallbackAndLayerStack() {
    GetWindow()->SetEventCallback(std::bind(&Quack::Application::OnEvent, this, std::placeholders::_1));
    GetLayerStack().Push(std::make_shared<LayerImGUI>());
}

void Quack::Application::SetDescription(const Quack::ApplicationDescription & desc) {
    _desc = desc;
}

Quack::Window * Quack::Application::GetWindow() {
    return _desc.Window;
}

void Quack::Application::SetWindow(Quack::Window * window) {
    _desc.Window = window;
}

Quack::GPUDevice * Quack::Application::GetDevice() {
    return _desc.GPUDevice;
}

void Quack::Application::SetDevice(Quack::GPUDevice * device) {
    _desc.GPUDevice = device;
}

Quack::LayerStack & Quack::Application::GetLayerStack() {
    return _desc.LayerStack;
}

void Quack::Application::SetLayerStack(const Quack::LayerStack & layerStack) {
    _desc.LayerStack = layerStack;
}

Quack::Scene * Quack::Application::GetScene() {
    return _desc.Scene;
}

void Quack::Application::SetScene(Quack::Scene * scene) {
    _desc.Scene = scene;
}

void Quack::Application::OnUpdate() {
    GetWindow()->OnUpdate();
    for (const auto & layer : GetLayerStack()) {
        layer->OnUpdate();
    }
}

