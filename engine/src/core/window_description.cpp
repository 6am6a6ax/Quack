#include "quack/core/window_description.h"

Quack::WindowDescription::WindowDescription() :
    _size(Size()),
    _position(Position()),
    _title("Unnamed"),
    _eventCallback(nullptr)
{}

const Quack::WindowDescription::Size &Quack::WindowDescription::GetSize() const {
    return _size;
}

void Quack::WindowDescription::SetSize(const Quack::WindowDescription::Size & size) {
    _size = size;
}

const Quack::WindowDescription::Position &Quack::WindowDescription::GetPosition() const {
    return _position;
}

void Quack::WindowDescription::SetPosition(const Quack::WindowDescription::Position & position) {
    _position = position;
}

const std::string &Quack::WindowDescription::GetTitle() const {
    return _title;
}

void Quack::WindowDescription::SetTitle(const std::string & title) {
    _title = title;
}

const Quack::WindowDescription::EventCallbackFn & Quack::WindowDescription::GetEventCallback() const {
    return _eventCallback;
}

void Quack::WindowDescription::SetEventCallback(const Quack::WindowDescription::EventCallbackFn & eventCallback) {
    _eventCallback = eventCallback;
}
