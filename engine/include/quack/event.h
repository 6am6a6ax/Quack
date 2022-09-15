#ifndef QUACK_EVENT_H
#define QUACK_EVENT_H

#include "event_type.h"

namespace Quack {
class Event {
public:
    virtual ~Event() = default;
    virtual const EventType GetType() const = 0;
};
}

#endif