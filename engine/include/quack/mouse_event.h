#ifndef QUACK_MOUSE_EVENT_H
#define QUACK_MOUSE_EVENT_H

#include <utility>

#include "event.h"
#include "event_type.h"

namespace Quack {
class MouseMovedEvent final : public Event {
public:
    explicit MouseMovedEvent(float && x, float && y) : _x(std::forward<float>(x)), _y(std::forward<float>(y)) {}

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
    const EventType GetType() const {
        return EventType::MouseButtonPressedEvent;
    }
};

class MouseButtonReleasedEvent final : public Event {
public:
    const EventType GetType() const {
        return EventType::MouseButtonReleasedEvent;
    }
};

class MouseScrolledEvent final : public Event {
public:
    const EventType GetType() const {
        return EventType::MouseScrolledEvent;
    }
};
}

#endif
