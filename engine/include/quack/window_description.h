#ifndef _WINDOW_DESCRIPTION_
#define _WINDOW_DESCRIPTION_

#include <string>
#include <cstdint>
#include <functional>

#include "event.h"

namespace Quack {
class WindowDescription {
public:
    WindowDescription();

    WindowDescription(const WindowDescription &) = default;
    WindowDescription(WindowDescription &&) = default;

    WindowDescription & operator=(const WindowDescription &) = default;
    WindowDescription & operator=(WindowDescription &&) = default;

    ~WindowDescription() = default;

public:
    using EventCallbackFn = std::function<void(Event &&)>;

    struct Size {
        uint32_t Width, Height;
    };

    class Position {
        uint32_t X, Y;
    };

public:
    const Size & GetSize() const;
    void SetSize(Size && size);

    const Position & GetPosition() const;
    void SetPosition(Position && position);

    const std::string & GetTitle() const;
    void SetTitle(std::string && title);

    const EventCallbackFn & GetEventCallback() const;
    void SetEventCallback(EventCallbackFn && eventCallback);

private:
    Size _size;
    Position _position;
    std::string _title;
    EventCallbackFn _eventCallback;
};
}

#endif