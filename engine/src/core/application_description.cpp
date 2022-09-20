#include "quack/core/application_description.h"

Quack::ApplicationDescription::ApplicationDescription() :
    _window(nullptr),
    _layerStack(LayerStack())
{}

Quack::Window * Quack::ApplicationDescription::GetWindow() {
    return *_window;
}

void Quack::ApplicationDescription::SetWindow(std::shared_ptr<Window*> window) {
    _window = std::forward<std::shared_ptr<Window*>>(window);
}

Quack::LayerStack & Quack::ApplicationDescription::GetLayerStack() {
    return _layerStack;
}

void Quack::ApplicationDescription::SetLayerStack(const Quack::LayerStack & layerStack) {
    _layerStack = layerStack;
}

Quack::GPUDevice *Quack::ApplicationDescription::GetDevice() {
    return _gpuDevice;
}

void Quack::ApplicationDescription::SetDevice(Quack::GPUDevice *gpuDevice) {
    _gpuDevice = gpuDevice;
}
