#include "quack/layer_imgui.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include <GL/glew.h>

#include "quack/application.h"

Quack::LayerImGUI::LayerImGUI() : Layer() {}

void Quack::LayerImGUI::OnAttach() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO & io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.DisplaySize = ImVec2(Quack::Application::GetInstance().GetDescription().GetWindow()->GetDescription().GetSize().Width,
                            Quack::Application::GetInstance().GetDescription().GetWindow()->GetDescription().GetSize().Height);

    ImGui_ImplOpenGL3_Init("#version 410");
}

void Quack::LayerImGUI::OnUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

//        float time = (float)glfwGetTime();
//
    ImGuiIO & io = ImGui::GetIO();
//    io.DisplaySize = ImVec2(Quack::Application::GetInstance().GetDescription().GetWindow()->GetDescription().GetSize().Width,
//                            Quack::Application::GetInstance().GetDescription().GetWindow()->GetDescription().GetSize().Height);
    io.DeltaTime = 1.0f;

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Quack::LayerImGUI::OnEvent(Quack::Event & e) {
    switch (e.GetType()) {
        case EventType::WindowResizedEvent:
            OnWindowResizedEvent(dynamic_cast<Quack::WindowResizedEvent &>(e));
            break;
        case EventType::KeyPressedEvent:
            OnKeyPressedEvent(dynamic_cast<Quack::KeyPressedEvent &>(e));
            break;
        case EventType::KeyReleasedEvent:
            OnKeyReleasedEvent(dynamic_cast<Quack::KeyReleasedEvent &>(e));
            break;
        case EventType::MouseMovedEvent:
            OnMouseMovedEvent(dynamic_cast<Quack::MouseMovedEvent &>(e));
            break;
        case EventType::MouseButtonPressedEvent:
            OnMouseButtonPressedEvent(dynamic_cast<Quack::MouseButtonPressedEvent &>(e));
            break;
        case EventType::MouseButtonReleasedEvent:
            OnMouseButtonReleasedEvent(dynamic_cast<Quack::MouseButtonReleasedEvent &>(e));
            break;
        case EventType::MouseScrolledEvent:
            OnMouseScrolledEvent(dynamic_cast<Quack::MouseScrolledEvent &>(e));
            break;
    }
}

#include <iostream>

void Quack::LayerImGUI::OnWindowResizedEvent(Quack::WindowResizedEvent & e) {
    ImGui::GetIO().DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    ImGui::GetIO().DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e.GetWidth(), e.GetHeight());

    std::cout << "Window resized!\n";
}

void Quack::LayerImGUI::OnMouseMovedEvent(Quack::MouseMovedEvent & e) {
    ImGui::GetIO().MousePos = ImVec2(e.GetX(), e.GetY());
}

void Quack::LayerImGUI::OnMouseScrolledEvent(Quack::MouseScrolledEvent & e) {
    ImGui::GetIO().MouseWheelH += e.GetXOffset();
    ImGui::GetIO().MouseWheel += e.GetYOffset();
}

void Quack::LayerImGUI::OnMouseButtonPressedEvent(Quack::MouseButtonPressedEvent & e) {
    ImGui::GetIO().MouseDown[static_cast<int>(e.GetMouseCode())] = true;
}

void Quack::LayerImGUI::OnMouseButtonReleasedEvent(Quack::MouseButtonReleasedEvent & e) {
    ImGui::GetIO().MouseDown[static_cast<int>(e.GetMouseCode())] = false;
}

void Quack::LayerImGUI::OnKeyPressedEvent(Quack::KeyPressedEvent & e) {

}

void Quack::LayerImGUI::OnKeyReleasedEvent(Quack::KeyReleasedEvent &) {

}