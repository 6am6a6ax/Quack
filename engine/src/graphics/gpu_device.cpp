#include "quack/quack.h"

Quack::GPUDevice::GPUDevice(const GPUDeviceDescription& desc) : _desc(desc) {}

const std::shared_ptr<Quack::GPUAdapter>& Quack::GPUDevice::GetAdapter() const {
    return _desc.Adapter;
}

const std::shared_ptr<Quack::GPUContext>& Quack::GPUDevice::GetContext() const {
    return _desc.Context;
}