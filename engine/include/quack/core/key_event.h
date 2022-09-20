#ifndef QUACK_KEY_EVENT_H
#define QUACK_KEY_EVENT_H

#include "event.h"
#include "event_type.h"

namespace Quack {
class KeyPressedEvent final : public Event {
public:
    const EventType GetType() const {
        return EventType::KeyPressedEvent;
    }
};

class KeyReleasedEvent final : public Event {
public:
    const EventType GetType() const {
        return EventType::KeyReleasedEvent;
    }
};
}

#endif
