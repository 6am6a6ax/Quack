#ifndef QUACK_WINDOW_EVENT_H
#define QUACK_WINDOW_EVENT_H

#include "event.h"
#include "event_type.h"

namespace Quack {
class WindowResizedEvent final : public Event {
public:
    const EventType GetType() const {
        return EventType::WindowResizedEvent;
    }
};
}

#endif
