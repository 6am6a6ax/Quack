#ifndef QUACK_WINDOW_H
#define QUACK_WINDOW_H

#include <string>

#include "event.h"
#include "event_type.h"
#include "mouse_event.h"
#include "window_event.h"

#include "layer_stack.h"
#include "window_description.h"

#include "quack/graphics/gpu_context.h"

namespace Quack {
class Window {
public:
    //explicit Window(const WindowDescription & description);
    explicit Window(const WindowDescription &);

public:
    virtual ~Window() = default;

public:
    static const Window * const Create(const WindowDescription &) = delete;

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
    WindowDescription & GetDescription() { return _description; }

protected:
    WindowDescription _description;
    GPUContext * _context;
};
}

#endif