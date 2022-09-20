#include "quack/platform/glfw/window_glfw.h"

#include "quack/core/mouse_event.h"
#include "quack/core/window_event.h"

#include "quack/platform/opengl/gpu_context_opengl.h"

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
    _context->SwapBuffers();
}

Quack::WindowGLFW::WindowGLFW(const Quack::WindowDescription & description)
    : Window(description)
{
    glfwInit();
    _window = glfwCreateWindow(static_cast<int>(_description.GetSize().Width),
                               static_cast<int>(_description.GetSize().Height),
                               _description.GetTitle().c_str(),
                               nullptr,
                               nullptr);


    _context = new GPUContextOpenGL(_window);
    _context->Init();

    glfwSetWindowUserPointer(_window, &_description);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow * window, int width, int height){
        auto desc = static_cast<WindowDescription *>(glfwGetWindowUserPointer(window));
        WindowResizedEvent e(width, height);
        desc->GetEventCallback()(e);
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow * window, double x, double y) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        MouseMovedEvent e(static_cast<float>(x), static_cast<float>(y));
        desc->GetEventCallback()(e);
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow * window, int button, int action, int mods) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent e(static_cast<MouseCode>(button));
                desc->GetEventCallback()(e);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent e(static_cast<MouseCode>(button));
                desc->GetEventCallback()(e);
                break;
            }
        }
    });

    glfwSetScrollCallback(_window, [](GLFWwindow * window, double xoffset, double yoffset) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent e(static_cast<float>(xoffset), static_cast<float>(yoffset));
        desc->GetEventCallback()(e);
    });

    glfwSetWindowSizeCallback(_window, [](GLFWwindow * window, int width, int height) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        WindowResizedEvent e(width, height);
        desc->GetEventCallback()(e);
    });
}

Quack::WindowGLFW::~WindowGLFW() {
    glfwDestroyWindow(_window);
}

void Quack::WindowGLFW::OnWindowResize(Quack::WindowResizedEvent & e) {
}

const GLFWwindow * const Quack::WindowGLFW::GetWindow() const {
    return _window;
}

Quack::Window * Quack::WindowGLFW::Create(const Quack::WindowDescription & description) {
    return new Quack::WindowGLFW(description);
}
