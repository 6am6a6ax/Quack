#ifndef QUACK_APPLICATION_EVENT_H
#define QUACK_APPLICATION_EVENT_H

#include "quack/core/event.h"

namespace Quack {
class ApplicationUpdated final : public Event {
public:
    ApplicationUpdated() = default;

public:
    EventType GetType() const {
        return EventType::ApplicationUpdated;
    }
};
}

#endif