#ifndef QUACK_KEY_EVENT_H
#define QUACK_KEY_EVENT_H

#include "quack/core/event.h"
#include "quack/core/event_type.h"

#include "quack/core/key_code.h"

namespace Quack {
class KeyPressedEvent final : public Event {
public:
    explicit KeyPressedEvent(const KeyCode& keyCode) : _keyCode(keyCode) {}

public:
    const EventType GetType() const {
        return EventType::KeyPressedEvent;
    }

    const KeyCode& GetKeyCode() const { return _keyCode; }

private:
    KeyCode _keyCode;
};

class KeyReleasedEvent final : public Event {
public:
    explicit KeyReleasedEvent(const KeyCode& keyCode) : _keyCode(keyCode) {}

public:
    const EventType GetType() const {
        return EventType::KeyReleasedEvent;
    }

    const KeyCode& GetKeyCode() const { return _keyCode; }

private:
    KeyCode _keyCode;
};
}

#endif
