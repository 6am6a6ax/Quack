#ifndef WINDOW_GLFW_H
#define WINDOW_GLFW_H

#include <GLFW/glfw3.h>

#include "quack/core/window.h"

#include <iostream>
#include <memory>

namespace Quack {
class WindowGLFW final : public Window {
public:
    explicit WindowGLFW(const WindowDescription &);

public:
    ~WindowGLFW() override;

public:
    static Window * Create(const WindowDescription &);

public:
    void Show() override;

    void Hide() override;
    void Minimize() override;

    void Maximize() override;
    void OnUpdate() override;

    void OnMouseMove(MouseMovedEvent &) override;
    void OnWindowResize(WindowResizedEvent &) override;

public:
    float GetTime() const override;

public:
    const GLFWwindow * const GetWindow() const;
    void SetWindow(GLFWwindow &);

    void* GetHandle() const override;

private:
    GLFWwindow* _window;
};
}

#endif
