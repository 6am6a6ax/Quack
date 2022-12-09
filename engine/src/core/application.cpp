#include "quack/quack.h"
#include "quack/core/timestep.h"
#include "quack/core/asset_library.h"

Quack::Application & Quack::Application::GetInstance() {
    static Application application;
    return application;
}

void Quack::Application::Init(const Quack::ApplicationDescription & description) {
    m_Description = description;
    BindBaseCallbackAndLayerStack();

    // TODO    
    m_Description.AssetLibrary = std::make_shared<AssetLibrary>();
}

void Quack::Application::Run() {
    float lastTime = 0.0f;
    m_Timestep = 0.0f;

    while (true) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        //ImGuizmo::BeginFrame();

        m_Description.Camera->OnUpdate(m_Timestep);

        OnUpdate();
        OnEvent(ApplicationUpdated{});

        float time = GetTime();
        m_Timestep = time - lastTime;
        lastTime = time;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void Quack::Application::OnEvent(Quack::Event& e) {
    m_Description.Window->OnEvent(e);
    m_Description.Camera->OnEvent(e);
    for (const auto & layer : m_Description.LayerStack ... )) {
        layer->OnEvent(e);
    }
}

void Quack::Application::OnUpdate() {
    GetWindow()->OnUpdate();
    for (const auto & layer : *GetLayerStack()) {
        layer->OnUpdate();
    }
}

const Quack::ApplicationDescription& Quack::Application::GetDescription() const {
    return m_Description;
}

void Quack::Application::BindBaseCallbackAndLayerStack() {
    m_Description.Window->SetEventCallback(std::bind(&Quack::Application::OnEvent, this, std::placeholders::_1));
    m_Description.LayerStack->Push(std::make_shared<LayerImGUI>());
}

std::shared_ptr<Quack::Window> Quack::Application::GetWindow() const {
    return m_Description.Window;
}

std::shared_ptr<Quack::GPUDevice> Quack::Application::GetDevice() const {
    return m_Description.GPUDevice;
}

std::shared_ptr<Quack::LayerStack> Quack::Application::GetLayerStack() const {
    return m_Description.LayerStack;
}

std::shared_ptr<Quack::Scene> Quack::Application::GetScene() const {
    return m_Description.Scene;
}

float Quack::Application::GetTime() const {
    return m_Description.Window->GetTime();
}

const Quack::Timestep& Quack::Application::GetTimestep() const {
    return m_Timestep;
}

std::shared_ptr<Quack::Camera> Quack::Application::GetCamera() const {
    return m_Description.Camera;
}

std::shared_ptr<Quack::AssetLibrary> Quack::Application::GetAssetLibrary() const {
    return m_Description.AssetLibrary;
}