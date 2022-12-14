#include "quack/core/asset_library.h"
#include "quack/core/timestep.h"
#include "quack/quack.h"

Quack::Application & Quack::Application::GetInstance() {
    static Application application;
    return application;
}

void Quack::Application::Init(const Quack::ApplicationDescription & desc) {
    SetDescription(desc);
    BindBaseCallbackAndLayerStack();
    _desc.AssetLibrary = std::make_shared<AssetLibrary>();
}

void Quack::Application::Run() {
    float lastTime = 0.0f;
    _timestep = 0.0f;

    while (true) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        //ImGuizmo::BeginFrame();

        _desc.Camera->OnUpdate(_timestep);

        OnUpdate();

        Quack::ApplicationUpdated e;
        OnEvent(e);

        float time = GetTime();
        _timestep = time - lastTime;
        lastTime = time;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void Quack::Application::OnEvent(Quack::Event & e) {
    GetWindow()->OnEvent(e);
    _desc.Camera->OnEvent(e);
    for (const auto & layer : *GetLayerStack()) {
        layer->OnEvent(e);
    }
}

const Quack::ApplicationDescription & Quack::Application::GetDescription() {
    return _desc;
}

void Quack::Application::BindBaseCallbackAndLayerStack() {
    GetWindow()->SetEventCallback(std::bind(&Quack::Application::OnEvent, this, std::placeholders::_1));
    GetLayerStack()->Push(std::make_shared<LayerImGUI>());
}

void Quack::Application::SetDescription(const Quack::ApplicationDescription & desc) {
    _desc = desc;
}

std::shared_ptr<Quack::Window> Quack::Application::GetWindow() {
    return _desc.Window;
}

void Quack::Application::SetWindow(std::shared_ptr<Quack::Window> window) {
    _desc.Window = window;
}

std::shared_ptr<Quack::GPUDevice> Quack::Application::GetDevice() {
    return _desc.GPUDevice;
}

void Quack::Application::SetDevice(std::shared_ptr<Quack::GPUDevice> device) {
    _desc.GPUDevice = device;
}

std::shared_ptr<Quack::LayerStack> Quack::Application::GetLayerStack() {
    return _desc.LayerStack;
}

void Quack::Application::SetLayerStack(std::shared_ptr<Quack::LayerStack> layerStack) {
    _desc.LayerStack = layerStack;
}

std::shared_ptr<Quack::Scene> Quack::Application::GetScene() {
    return _desc.Scene;
}

void Quack::Application::SetScene(std::shared_ptr<Quack::Scene> scene) {
    _desc.Scene = scene;
}

void Quack::Application::OnUpdate() {
    GetWindow()->OnUpdate();
    for (const auto & layer : *GetLayerStack()) {
        layer->OnUpdate();
    }
}

float Quack::Application::GetTime() const {
    return _desc.Window->GetTime();
}

const Quack::Timestep& Quack::Application::GetTimestep() const {
    return _timestep;
}