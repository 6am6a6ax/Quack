#include "quack/quack.h"

// Quack::GPUContext::GPUContext(const Quack::GPUContext::Desciption& desc) : _desc(desc) {}

const Quack::GPUContext::Description& Quack::GPUContext::GetDescription() const {
    return _desc;
}

void Quack::GPUContext::SetDescription(const Quack::GPUContext::Description& desc) {
    _desc = desc;
}