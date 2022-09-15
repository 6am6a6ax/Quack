#include "quack/window.h"

//Quack::Window::Window(const Quack::WindowDescription & description) :
//    _description(description)
//{}

Quack::Window::Window(Quack::WindowDescription && description) :
    _description(std::forward<Quack::WindowDescription>(description))
{}

void Quack::Window::OnEvent(Quack::Event && e) {
    switch (e.GetType()) {
        case EventType::WindowResizedEvent:
            OnWindowResize(std::forward<WindowResizedEvent>(dynamic_cast<WindowResizedEvent &&>(e)));
            break;

        case EventType::MouseMovedEvent:
            OnMouseMove(std::forward<MouseMovedEvent>(dynamic_cast<MouseMovedEvent &&>(e)));
            break;
    }
}
