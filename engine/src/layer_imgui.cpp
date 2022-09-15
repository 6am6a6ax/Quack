#include "quack/layer_imgui.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include "quack/application.h"

Quack::LayerImGUI::LayerImGUI() : Layer() {}

void Quack::LayerImGUI::OnAttach() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO & io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplOpenGL3_Init("#version 410");
}

void Quack::LayerImGUI::OnUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

//        float time = (float)glfwGetTime();
//
    ImGuiIO & io = ImGui::GetIO();
    io.DisplaySize = ImVec2(1280.0f, 720.0f);
    io.DeltaTime = 1.0f;

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Quack::LayerImGUI::OnEvent(Quack::Event && e) {
    switch (e.GetType()) {
        case EventType::WindowResizedEvent:
            OnWindowResizedEvent(dynamic_cast<Quack::WindowResizedEvent &&>(e));
            break;
        case EventType::KeyPressedEvent:
            OnKeyPressedEvent(dynamic_cast<Quack::KeyPressedEvent &&>(e));
            break;
        case EventType::KeyReleasedEvent:
            OnKeyReleasedEvent(dynamic_cast<Quack::KeyReleasedEvent &&>(e));
            break;
        case EventType::MouseMovedEvent:
            OnMouseMovedEvent(dynamic_cast<Quack::MouseMovedEvent &&>(e));
            break;
        case EventType::MouseButtonPressedEvent:
            OnMouseButtonPressedEvent(dynamic_cast<Quack::MouseButtonPressedEvent &&>(e));
            break;
        case EventType::MouseButtonReleasedEvent:
            OnMouseButtonReleasedEvent(dynamic_cast<Quack::MouseButtonReleasedEvent &&>(e));
            break;
        case EventType::MouseScrolledEvent:
            OnMouseScrolledEvent(dynamic_cast<Quack::MouseScrolledEvent &&>(e));
            break;
    }
}

void Quack::LayerImGUI::OnWindowResizedEvent(Quack::WindowResizedEvent && e) {

}

void Quack::LayerImGUI::OnMouseMovedEvent(Quack::MouseMovedEvent && e) {

}

void Quack::LayerImGUI::OnMouseScrolledEvent(Quack::MouseScrolledEvent && e) {

}

void Quack::LayerImGUI::OnMouseButtonPressedEvent(Quack::MouseButtonPressedEvent && e) {
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown
}

void Quack::LayerImGUI::OnMouseButtonReleasedEvent(Quack::MouseButtonReleasedEvent && e) {

}

void Quack::LayerImGUI::OnKeyPressedEvent(Quack::KeyPressedEvent && e) {

}

void Quack::LayerImGUI::OnKeyReleasedEvent(Quack::KeyReleasedEvent &&) {

}