#include "quack/quack.h"

Quack::GPUContext::GPUContext(const Quack::GPUContext::Description& desc) : _desc(desc) {}

const Quack::GPUContext::Description& Quack::GPUContext::GetDescription() const {
    return _desc;
}

const std::shared_ptr<Quack::Window>& Quack::GPUContext::GetWindow() const {
    return _desc.Window;
}