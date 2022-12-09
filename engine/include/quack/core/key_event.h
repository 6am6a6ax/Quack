#ifndef QUACK_KEY_EVENT_H
#define QUACK_KEY_EVENT_H

#include "quack/core/event.h"
#include "quack/core/key_code.h"

namespace Quack {
class KeyEvent : public Event {
public:
    explicit KeyEvent(const KeyCode&);

public:
    const KeyCode& GetKeyCode() const; 

private:
    KeyCode m_KeyCode;
};

class KeyPressedEvent final : public KeyEvent {
public:
    explicit KeyPressedEvent(const KeyCode&);

public:
    EventType GetType() const;
};

class KeyReleasedEvent final : public KeyEvent {
public:
    explicit KeyReleasedEvent(const KeyCode&);

public:
    EventType GetType() const;
};
}

#endif
