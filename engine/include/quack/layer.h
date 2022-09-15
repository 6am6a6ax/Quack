#ifndef QUACK_LAYER_H
#define QUACK_LAYER_H

#include <string>

#include "event.h"

namespace Quack {
class Layer {
public:
    Layer() : _name("Unnamed layer") {}
    explicit Layer(std::string && name) : _name(std::forward<const std::string>(name)) {}

    virtual ~Layer() = default;

public:
    virtual void OnAttach() {}
    virtual void OnDetach() {}

    virtual void OnUpdate() {}
    virtual void OnEvent(Event &&) {}

    const std::string & GetName() const { return _name; }
    void SetName(std::string && name) { _name = std::forward<std::string>(name); }

private:
    std::string _name;
};
}

#endif
