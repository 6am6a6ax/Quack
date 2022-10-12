#include "quack/quack.h"

Quack::Window::Window(const Quack::WindowDescription & desc) : _desc(desc) {}

void Quack::Window::OnEvent(Quack::Event & e) {
    switch (e.GetType()) {
        case EventType::WindowResizedEvent:
            OnWindowResize(dynamic_cast<WindowResizedEvent &>(e));
            break;
        case EventType::MouseMovedEvent:
            OnMouseMove(dynamic_cast<MouseMovedEvent &>(e));
            break;
    }
}

const Quack::WindowDescription &Quack::Window::GetDescription() {
    return _desc;
}

void Quack::Window::SetDescription(const Quack::WindowDescription & desc) {
    _desc = desc;
}

const Quack::WindowDescription::Size & Quack::Window::GetSize() const {
    return _desc.WindowSize;
}

void Quack::Window::SetSize(const Quack::WindowDescription::Size & size) {
    _desc.WindowSize = size;
}

const Quack::WindowDescription::Position &Quack::Window::GetPosition() const {
    return _desc.Pos;
}

void Quack::Window::SetPosition(const Quack::WindowDescription::Position & position) {
    _desc.Pos = position;
}

const Quack::WindowDescription::EventCallbackFn &Quack::Window::GetEventCallback() const {
    return _desc.EventCallback;
}

void Quack::Window::SetEventCallback(const Quack::WindowDescription::EventCallbackFn & eventCallback) {
    _desc.EventCallback = eventCallback;
}

const std::string & Quack::Window::GetTitle() const {
    return _desc.Title;
}

void Quack::Window::SetTitle(const std::string & title) {
    _desc.Title = title;
}

Quack::GPUContext * Quack::Window::GetContext() {
    return _desc.Context;
}

void Quack::Window::SetContext(Quack::GPUContext * context) {
    _desc.Context = context;
}