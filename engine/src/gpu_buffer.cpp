#include "quack/gpu_buffer.h"

Quack::GPUBuffer::GPUBuffer() : _desc(GPUBufferDescription()) {}
Quack::GPUBuffer::GPUBuffer(Quack::GPUBufferDescription desc) : _desc(desc) {}

Quack::GPUBuffer::GPUBuffer(const Quack::GPUBuffer &)  = default;
Quack::GPUBuffer::GPUBuffer(Quack::GPUBuffer &&) noexcept = default;

Quack::GPUBuffer & Quack::GPUBuffer::operator=(const Quack::GPUBuffer &) = default;
Quack::GPUBuffer & Quack::GPUBuffer::operator=(Quack::GPUBuffer &&) noexcept = default;

Quack::GPUBuffer::~GPUBuffer() = default;

const uint32_t & Quack::GPUBuffer::GetSize() const {
    return _desc.Size;
}

const uint32_t &Quack::GPUBuffer::GetStride() const {
    return _desc.Stride;
}

const uint32_t Quack::GPUBuffer::GetElementsCount() const {
    return _desc.Size / _desc.Stride;
}

const Quack::GPUPixelFormat & Quack::GPUBuffer::GetFormat() const {
    return _desc.Format;
}

const Quack::GPUResourceUsage & Quack::GPUBuffer::GetUsage() const {
    return _desc.Usage;
}

const Quack::GPUBufferUtility & Quack::GPUBuffer::GetUtility() const {
    return _desc.Utility;
}

const Quack::GPUBufferDescription & Quack::GPUBuffer::GetDescription() const {
    return _desc;
}
