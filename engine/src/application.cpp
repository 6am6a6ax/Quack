#include "quack/application.h"

#include "quack/window_glfw.h"

#include "quack/layer_imgui.h"

Quack::Application & Quack::Application::GetInstance() {
    static Application application;
    return application;
}

void Quack::Application::Init(const Quack::WindowDescription & windowDescription) {
    _description.SetWindow(std::make_shared<Quack::Window*>(Quack::WindowGLFW::Create(windowDescription)));

    // TODO
    //_description.GetWindow()->GetDescription().SetEventCallback(std::bind(&Quack::WindowGLFW::OnEvent, std::ref(*_description.GetWindow()), std::placeholders::_1));
    _description.GetWindow()->GetDescription().SetEventCallback(std::bind(&Quack::Application::OnEvent, this, std::placeholders::_1));

    _description.GetLayerStack().Push(std::make_shared<LayerImGUI>());
}


void Quack::Application::Run() {
    while (true) {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (const auto & layer : _description.GetLayerStack()) {
            layer->OnUpdate();
        }
        _description.GetWindow()->OnUpdate();
    }
}

void Quack::Application::OnEvent(Quack::Event & e) {
    _description.GetWindow()->OnEvent(e);
    for (const auto & layer : _description.GetLayerStack()) {
        layer->OnEvent(e);
    }
}

Quack::ApplicationDescription & Quack::Application::GetDescription() {
    return _description;
}

void Quack::Application::SetDescription(Quack::ApplicationDescription & description) {
    _description = std::forward<Quack::ApplicationDescription>(description);
}

