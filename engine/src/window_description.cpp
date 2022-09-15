#include "quack/window_description.h"

Quack::WindowDescription::WindowDescription() :
    _size(Size()),
    _position(Position()),
    _title("Unnamed"),
    _eventCallback(nullptr)
{}

const Quack::WindowDescription::Size &Quack::WindowDescription::GetSize() const {
    return _size;
}

void Quack::WindowDescription::SetSize(Quack::WindowDescription::Size && size) {
    _size = std::forward<Quack::WindowDescription::Size>(size);
}

const Quack::WindowDescription::Position &Quack::WindowDescription::GetPosition() const {
    return _position;
}

void Quack::WindowDescription::SetPosition(Quack::WindowDescription::Position && position) {
    _position = std::forward<Quack::WindowDescription::Position>(position);
}

const std::string &Quack::WindowDescription::GetTitle() const {
    return _title;
}

void Quack::WindowDescription::SetTitle(std::string && title) {
    _title = std::forward<std::string>(title);
}

const Quack::WindowDescription::EventCallbackFn & Quack::WindowDescription::GetEventCallback() const {
    return _eventCallback;
}

void Quack::WindowDescription::SetEventCallback(Quack::WindowDescription::EventCallbackFn && eventCallback) {
    _eventCallback = std::forward<Quack::WindowDescription::EventCallbackFn>(eventCallback);
}
