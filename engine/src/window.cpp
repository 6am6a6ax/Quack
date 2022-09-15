#include "quack/window.h"

//Quack::Window::Window(const Quack::WindowDescription & description) :
//    _description(description)
//{}

Quack::Window::Window(const Quack::WindowDescription & description) :
    _description(description)
{}

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
