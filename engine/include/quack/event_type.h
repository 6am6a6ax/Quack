#ifndef QUACK_EVENT_TYPE_H
#define QUACK_EVENT_TYPE_H

namespace Quack {
enum class EventType {
    WindowResizedEvent,
    KeyPressedEvent, KeyReleasedEvent,
    MouseMovedEvent, MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseScrolledEvent
};
}

#endif
