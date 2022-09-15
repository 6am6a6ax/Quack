#include "quack/application.h"

#include "quack/window_glfw.h"

#include "quack/layer_imgui.h"

Quack::Application & Quack::Application::GetInstance() {
    static Application application;
    return application;
}

void Quack::Application::Init(Quack::WindowDescription && windowDescription) {
    _description.SetWindow(std::make_shared<Quack::Window*>(Quack::WindowGLFW::Create(std::forward<Quack::WindowDescription>(windowDescription))));

    // TODO
    _description.GetWindow()->GetDescription().SetEventCallback(std::bind(&Quack::WindowGLFW::OnEvent, std::ref(*_description.GetWindow()), std::placeholders::_1));

    _description.GetLayerStack().Push(std::make_shared<LayerImGUI>());
}


void Quack::Application::Run() {
    while (true) {
        _description.GetWindow()->OnUpdate();

        for (const auto & layer : _description.GetLayerStack()) {
            layer->OnUpdate();
        }
    }
}

void Quack::Application::OnEvent(Quack::Event && event) const {

}

const Quack::ApplicationDescription & Quack::Application::GetDescription() const {
    return _description;
}

void Quack::Application::SetDescription(Quack::ApplicationDescription && description) {
    _description = std::forward<Quack::ApplicationDescription>(description);
}

