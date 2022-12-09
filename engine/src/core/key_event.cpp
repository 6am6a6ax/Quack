#include "quack/core/key_event.h"

Quack::KeyEvent::KeyEvent(const KeyCode& keyCode) : m_KeyCode(keyCode) {}

const Quack::KeyCode& Quack::KeyEvent::GetKeyCode() const {
    return m_KeyCode;
}

Quack::KeyPressedEvent::KeyPressedEvent(const Quack::KeyCode& keyCode) : Quack::KeyEvent(keyCode) {}

Quack::EventType Quack::KeyPressedEvent::GetType() const {
    return EventType::KeyPressedEvent;
}

Quack::KeyReleasedEvent::KeyReleasedEvent(const Quack::KeyCode& keyCode) : Quack::KeyEvent(keyCode) {}

Quack::EventType Quack::KeyReleasedEvent::GetType() const {
    return EventType::KeyReleasedEvent;
}