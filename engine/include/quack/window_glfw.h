#ifndef WINDOW_GLFW_H
#define WINDOW_GLFW_H

#include <GLFW/glfw3.h>

#include "window.h"

#include <iostream>

namespace Quack {
class WindowGLFW final : public Window {
public:
    explicit WindowGLFW(WindowDescription &&);

    WindowGLFW(const WindowGLFW &) = default;
    WindowGLFW(WindowGLFW &&) noexcept = default;

    WindowGLFW & operator=(const WindowGLFW &) = default;
    WindowGLFW & operator=(WindowGLFW &&) noexcept = default;

public:
    ~WindowGLFW() override;

public:
    static Window * Create(WindowDescription &&);

public:
    void Show() override;

    void Hide() override;
    void Minimize() override;

    void Maximize() override;
    void OnUpdate() override;

    void OnMouseMove(MouseMovedEvent &&) override;
    void OnWindowResize(WindowResizedEvent &&) override;

public:
    const GLFWwindow * const GetWindow() const;
    void SetWindow(const GLFWwindow &);

private:
    GLFWwindow * _window;
};
}

#endif
