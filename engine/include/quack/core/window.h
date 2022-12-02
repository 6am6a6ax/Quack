#ifndef QUACK_WINDOW_H
#define QUACK_WINDOW_H

#include <string>
#include <functional>

#include "event.h"
#include "event_type.h"
#include "mouse_event.h"
#include "window_event.h"

#include "layer_stack.h"

#include "quack/graphics/gpu_context.h"

namespace Quack {
struct WindowDescription {
    struct Size {
        uint32_t Width;
        uint32_t Height;
    } WindowSize;

    struct Position {
        uint32_t X;
        uint32_t Y;
    } Pos;

    std::string Title;
    std::shared_ptr<GPUContext> Context;

    using EventCallbackFn = std::function<void(Event &)>;
    Quack::WindowDescription::EventCallbackFn EventCallback;
};

class Window {
public:
    explicit Window(const WindowDescription &);
    virtual ~Window() = default;

public:
    virtual void Show() = 0;
    virtual void Hide() = 0;

    virtual void Minimize() = 0;
    virtual void Maximize() = 0;

public:
    virtual void OnUpdate() = 0;
    virtual void OnEvent(Event & e);

public:
    virtual void OnMouseMove(MouseMovedEvent &) = 0;
    virtual void OnWindowResize(WindowResizedEvent &) = 0;

public:
    virtual float GetTime() const = 0;

public:
    const WindowDescription & GetDescription();
    void SetDescription(const WindowDescription &);

    const WindowDescription::Size & GetSize() const;
    void SetSize(const WindowDescription::Size &);

    const WindowDescription::Position & GetPosition() const;
    void SetPosition(const WindowDescription::Position &);

    const WindowDescription::EventCallbackFn & GetEventCallback() const;
    void SetEventCallback(const WindowDescription::EventCallbackFn &);

    const std::string & GetTitle() const;
    void SetTitle(const std::string &);

    std::shared_ptr<GPUContext> GetContext();
    void SetContext(std::shared_ptr<GPUContext>);

protected:
    WindowDescription _desc;
};
}

#endif