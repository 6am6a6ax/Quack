#ifndef _WINDOW_DESCRIPTION_
#define _WINDOW_DESCRIPTION_

#include <string>
#include <cstdint>

namespace Quack {
enum class WindowStatus {
    Minimized,
    Maximized
};

struct WindowSize {
    uint32_t Width;
    uint32_t Height;
};

struct WindowPosition {
    uint32_t X;
    uint32_t Y;
};

struct WindowDescription {
    bool Visible;
    bool Focused;
    bool Fullscreen;
    WindowStatus Status;

    std::string Title;

    WindowSize Size;
    WindowPosition Position;
};
}

#endif