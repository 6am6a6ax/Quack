#include "quack/quack.h"

Quack::WindowGLFW::WindowGLFW(const Quack::WindowDescription & desc) : Window(desc)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(static_cast<int>(GetSize().Width),
                               static_cast<int>(GetSize().Height),
                               GetTitle().c_str(),
                               nullptr,
                               nullptr);

    glfwSetWindowUserPointer(_window, &_desc);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow * window, int width, int height){
        auto desc = static_cast<WindowDescription *>(glfwGetWindowUserPointer(window));
        WindowResizedEvent e(width, height);
        desc->EventCallback(e);
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow * window, double x, double y) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));

        static float lastX;
        static float lastY;

        MouseMovedEvent e(static_cast<float>(x), static_cast<float>(y), lastX, lastY);

        lastX = static_cast<float>(x);
        lastY = static_cast<float>(y);

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

    glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto desc = static_cast<WindowDescription*>(glfwGetWindowUserPointer(window));
        switch(action) {
            case GLFW_PRESS: {
                KeyPressedEvent event { static_cast<KeyCode>(key) };
                desc->EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event { static_cast<KeyCode>(key) };
                desc->EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event { static_cast<KeyCode>(key) };
                desc->EventCallback(event);
                break;
            }
        }
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
}

void Quack::WindowGLFW::OnWindowResize(Quack::WindowResizedEvent & e) {
}

float Quack::WindowGLFW::GetTime() const {
    return glfwGetTime();
}

void* Quack::WindowGLFW::GetHandle() const {
    return (void*)_window;
}

GLFWwindow* const Quack::WindowGLFW::GetWindow() {
    return _window;
}