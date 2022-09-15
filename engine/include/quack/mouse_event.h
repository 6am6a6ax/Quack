#ifndef QUACK_MOUSE_EVENT_H
#define QUACK_MOUSE_EVENT_H

#include <utility>

#include "event.h"
#include "event_type.h"

#include "mouse_code.h"

namespace Quack {
class MouseMovedEvent final : public Event {
public:
    explicit MouseMovedEvent(const float & x, const float & y) : _x(x), _y(y) {}

public:
    const EventType GetType() const {
        return EventType::MouseMovedEvent;
    }

    const float & GetX() const { return _x; }
    const float & GetY() const { return _y; }

private:
    float _x, _y;
};

class MouseButtonPressedEvent final : public Event {
public:
    explicit MouseButtonPressedEvent(const MouseCode & mouseCode) : _mouseCode(mouseCode) {}

public:
    const EventType GetType() const {
        return EventType::MouseButtonPressedEvent;
    }

    const MouseCode & GetMouseCode() const { return _mouseCode; }

private:
    MouseCode _mouseCode;
};

class MouseButtonReleasedEvent final : public Event {
public:
    explicit MouseButtonReleasedEvent(const MouseCode & mouseCode) : _mouseCode(mouseCode) {}

public:
    const EventType GetType() const {
        return EventType::MouseButtonReleasedEvent;
    }

    const MouseCode & GetMouseCode() const { return _mouseCode; }

private:
    MouseCode _mouseCode;
};

class MouseScrolledEvent final : public Event {
public:
    explicit MouseScrolledEvent(const float & xOffset, const float & yOffset) : _xOffset(xOffset), _yOffset(yOffset) {}

public:
    const EventType GetType() const {
        return EventType::MouseScrolledEvent;
    }

    const float & GetXOffset() const { return _xOffset; }
    const float & GetYOffset() const { return _yOffset; }

private:
    float _xOffset, _yOffset;
};
}

#endif
