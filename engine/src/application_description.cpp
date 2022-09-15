#include "quack/application_description.h"

Quack::ApplicationDescription::ApplicationDescription() :
    _window(nullptr),
    _layerStack(LayerStack())
{}

Quack::Window * Quack::ApplicationDescription::GetWindow() {
    return *_window;
}

void Quack::ApplicationDescription::SetWindow(std::shared_ptr<Window*> && window) {
    _window = std::forward<std::shared_ptr<Window*>>(window);
}

Quack::LayerStack & Quack::ApplicationDescription::GetLayerStack() {
    return _layerStack;
}

void Quack::ApplicationDescription::SetLayerStack(Quack::LayerStack && layerStack) {
    _layerStack = std::forward<Quack::LayerStack>(layerStack);
}
