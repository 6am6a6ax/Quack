#include "quack/quack.h"

Quack::GPUSwapChain::GPUSwapChain(const GPUSwapChainDescription& desc) : _desc(desc) {}

const std::shared_ptr<Quack::GPUContext>& Quack::GPUSwapChain::GetContext() const {
    return _desc.Context;
}

const std::shared_ptr<Quack::GPUAdapter>& Quack::GPUSwapChain::GetAdapter() const {
    return _desc.Adapter;
}

const std::shared_ptr<Quack::GPUDevice>& Quack::GPUSwapChain::GetDevice() const {
    return _desc.Device;
}

const std::shared_ptr<Quack::Window>& Quack::GPUSwapChain::GetWindow() const {
    return _desc.Window;
}

const std::shared_ptr<Quack::GPUShaderProgram>& Quack::GPUSwapChain::GetVertex() const {
    return _desc.Vertex;
}

const std::shared_ptr<Quack::GPUShaderProgram>& Quack::GPUSwapChain::GetFragment() const {
    return _desc.Fragment;
}