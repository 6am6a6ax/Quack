#ifndef QUACK_WINDOW_EVENT_H
#define QUACK_WINDOW_EVENT_H

#include "event.h"
#include "event_type.h"

namespace Quack {
class WindowResizedEvent final : public Event {
public:
    explicit WindowResizedEvent(const int & width, const int & height) : _width(width), _height(height) {}

public:
    const EventType GetType() const {
        return EventType::WindowResizedEvent;
    }

    const int & GetWidth() const { return _width; }
    const int & GetHeight() const { return _height; }

private:
    int _width, _height;
};
}

#endif
