#include "quack/quack.h"

Quack::LayerImGUI::LayerImGUI() : Layer() {}

void Quack::LayerImGUI::OnAttach() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO & io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.DisplaySize = ImVec2(Quack::Application::GetInstance().GetWindow()->GetSize().Width,
                            Quack::Application::GetInstance().GetWindow()->GetSize().Height);

    ImGui_ImplOpenGL3_Init("#version 410");

}

void Quack::LayerImGUI::OnUpdate() {
    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    style.WindowMinSize.x = minWinSizeX;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();


//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui::NewFrame();

//        float time = (float)glfwGetTime();
//
//    io.DisplaySize = ImVec2(Quack::Application::GetInstance().GetWindow()->GetSize().Width,
//                            Quack::Application::GetInstance().GetWindow()->GetSize().Height);
    io.DeltaTime = 1.0f;
//
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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