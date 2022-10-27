#include "quack/quack.h"

Quack::GPUAdapter::GPUAdapter(const Quack::GPUAdapterDescription& desc) : _desc(desc) {}

const Quack::GPUAdapterDescription& Quack::GPUAdapter::GetDescription() const {
    return _desc;
}

const std::shared_ptr<Quack::GPUContext>& Quack::GPUAdapter::GetContext() const {
    return _desc.Context;
}