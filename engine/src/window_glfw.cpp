#include "quack/window_glfw.h"

void Quack::WindowGLFW::Show() {
    glfwShowWindow(_window);
}

void Quack::WindowGLFW::Hide() {
    glfwHideWindow(_window);
}

void Quack::WindowGLFW::Minimize() {
    glfwIconifyWindow(_window);
}

void Quack::WindowGLFW::Maximize() {
    glfwMaximizeWindow(_window);
}

void Quack::WindowGLFW::OnMouseMove(MouseMovedEvent && event) {
    std::cout << "Mouse moved!\t" << "X: " << event.GetX() << "\t" << "Y: " << event.GetY() << "\n";
}


void Quack::WindowGLFW::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

Quack::WindowGLFW::WindowGLFW(Quack::WindowDescription && description)
    : Window(std::forward<Quack::WindowDescription>(description))
{
    glfwInit();
    _window = glfwCreateWindow(static_cast<int>(_description.GetSize().Width),
                               static_cast<int>(_description.GetSize().Height),
                               _description.GetTitle().c_str(),
                               nullptr,
                               nullptr);

    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, &_description);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow * window, int width, int height){
        auto desc = static_cast<WindowDescription *>(glfwGetWindowUserPointer(window));
        desc->GetEventCallback()(WindowResizedEvent());
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow * window, double x, double y) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        desc->GetEventCallback()(MouseMovedEvent(static_cast<float>(x), static_cast<float>(y)));
    });
}

Quack::WindowGLFW::~WindowGLFW() {
    glfwDestroyWindow(_window);
}

void Quack::WindowGLFW::OnWindowResize(Quack::WindowResizedEvent && e) {
    std::cout << "Window has been resized\n";
}

const GLFWwindow * const Quack::WindowGLFW::GetWindow() const {
    return _window;
}

Quack::Window * Quack::WindowGLFW::Create(Quack::WindowDescription && description) {
    return new Quack::WindowGLFW(std::forward<Quack::WindowDescription>(description));
}
