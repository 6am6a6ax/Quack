#include "quack/graphics/gpu_buffer.h"
#include "quack/quack.h"

Quack::Application & Quack::Application::GetInstance() {
    static Application application;
    return application;
}

void Quack::Application::Init(const Quack::ApplicationDescription & desc) {
    SetDescription(desc);
    BindBaseCallbackAndLayerStack();
    _desc.AssetLibrary = AssetLibrary();
    _desc.GPUContext->Init();
}

void Quack::Application::Run() {
    float lastTime = 0.0f;
    _timestep = 0.0f;

    // while (true) {
        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplVulkan_NewFrame();
        // ImGui::NewFrame();
        //ImGuizmo::BeginFrame();

        // _desc.Camera->OnUpdate(_timestep);

        // OnUpdate();

        // Quack::ApplicationUpdated e;
        // OnEvent(e);

        // float time = GetTime();
        // _timestep = time - lastTime;
        // lastTime = time;

        // // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), VkCommandBuffer());
    // }
}

void Quack::Application::OnEvent(Quack::Event & e) {
    // GetWindow()->OnEvent(e);
    // _desc.Camera->OnEvent(e);
    // for (const auto & layer : GetLayerStack()) {
    //     layer->OnEvent(e);
    // }
}

const Quack::ApplicationDescription & Quack::Application::GetDescription() {
    return _desc;
}

void Quack::Application::BindBaseCallbackAndLayerStack() {
    GetWindow()->SetEventCallback(std::bind(&Quack::Application::OnEvent, this, std::placeholders::_1));
    //GetLayerStack().Push(std::make_shared<LayerImGUI>());
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
    // GetWindow()->OnUpdate();
    // for (const auto & layer : GetLayerStack()) {
    //     layer->OnUpdate();
    // }

    GetContext()->SwapBuffers();
}

float Quack::Application::GetTime() const {
    return _desc.Window->GetTime();
}

const Quack::Timestep& Quack::Application::GetTimestep() const {
    return _timestep;
}

Quack::GPUContext* Quack::Application::GetContext() const {
    return _desc.GPUContext;
}