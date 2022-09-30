#include "quack/quack.h"

Quack::WindowGLFW::WindowGLFW(const Quack::WindowDescription & desc) : Window(desc)
{
    glfwInit();
    _window = glfwCreateWindow(static_cast<int>(GetSize().Width),
                               static_cast<int>(GetSize().Height),
                               GetTitle().c_str(),
                               nullptr,
                               nullptr);

    SetContext(new GPUContextOpenGL(_window));
    GetContext()->Init();

    glfwSetWindowUserPointer(_window, &_desc);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow * window, int width, int height){
        auto desc = static_cast<WindowDescription *>(glfwGetWindowUserPointer(window));
        WindowResizedEvent e(width, height);
        desc->EventCallback(e);
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow * window, double x, double y) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        MouseMovedEvent e(static_cast<float>(x), static_cast<float>(y));
        desc->EventCallback(e);
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow * window, int button, int action, int mods) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent e(static_cast<MouseCode>(button));
                desc->EventCallback(e);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent e(static_cast<MouseCode>(button));
                desc->EventCallback(e);
                break;
            }
        }
    });

    glfwSetScrollCallback(_window, [](GLFWwindow * window, double xoffset, double yoffset) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent e(static_cast<float>(xoffset), static_cast<float>(yoffset));
        desc->EventCallback(e);
    });

    glfwSetWindowSizeCallback(_window, [](GLFWwindow * window, int width, int height) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        WindowResizedEvent e(width, height);
        desc->EventCallback(e);
    });
}

Quack::WindowGLFW::~WindowGLFW() {
    glfwDestroyWindow(_window);
}

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

void Quack::WindowGLFW::OnMouseMove(MouseMovedEvent & event) {
}


void Quack::WindowGLFW::OnUpdate() {
    glfwPollEvents();
    GetContext()->SwapBuffers();
}

void Quack::WindowGLFW::OnWindowResize(Quack::WindowResizedEvent & e) {
}
