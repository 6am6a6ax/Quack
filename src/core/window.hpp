#ifndef _WINDOW_
#define _WINDOW_

#include <string>

#include "window_description.hpp"

namespace Quack {
class Window {
public:
    Window() = default;
    Window(WindowDescription desc) : _desc(desc) {}

    Window(Window const &) = default;
    Window(Window &&) = default;

    Window & operator=(Window const &) = default;
    Window & operator=(Window &&) = default;

public:
    virtual ~Window() = default;

public:
    virtual void Show() = 0;
    virtual void Hide() = 0;

    virtual void Minimize() = 0;
    virtual void Maximize() = 0;

public:
    virtual void OnShow() = 0;
    virtual void OnHide() = 0;
    virtual void OnResize() = 0;
    virtual void OnClosing() = 0;
    virtual void OnClosed() = 0;
    virtual void OnFocus() = 0;
    virtual void OnLostFocus() = 0;

public:
    virtual void OnKeyUp() = 0;
    virtual void OnKeyDown() = 0;
    virtual void OnMouseUp() = 0;
    virtual void OnMouseDown() = 0;
    // virtual void OnMouseDoubleClick() = 0;
    virtual void OnMouseWheel() = 0;
    virtual void OnMouseMove() = 0;
    virtual void OnMouseLeave() = 0;

public:
    virtual void GetMousePosition() = 0;
    virtual void SetMousePosition() = 0;

public:
    WindowDescription GetDescription() const { return _desc; }

    WindowSize GetSize() const { return _desc.Size; }
    std::string GetTitle() const { return _desc.Title; }
    WindowStatus GetStatus() const { return _desc.Status; }

    WindowPosition GetPosition() const { return _desc.Position; }

    bool IsVisible() const { return _desc.Visible; }
    bool IsFullscreen() const { return _desc.Fullscreen; }
    bool IsWindowed() const { return !_desc.Fullscreen; }
    bool IsFocused() const { return _desc.Focused; }

private:
    WindowDescription _desc;
};
}

#endif