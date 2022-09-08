#ifndef _GPU_BUFFER_
#define _GPU_BUFFER_

#include <cstdint>

#include "gpu_resource.hpp"
#include "gpu_resource_usage.hpp"

#include "gpu_buffer_utility.hpp"
#include "gpu_buffer_description.hpp"

#include "gpu_pixel_format.hpp"

namespace Quack {
class GPUBuffer : public GPUResource {
public:
    GPUBuffer() : _desc(GPUBufferDescription()) {}
    explicit GPUBuffer(GPUBufferDescription desc) : _desc(desc) {}

    GPUBuffer(GPUBuffer const &) = default;
    GPUBuffer(GPUBuffer &&) = default;

    GPUBuffer & operator=(GPUBuffer const &) = default;
    GPUBuffer & operator=(GPUBuffer &&) = default;

public:
    virtual ~GPUBuffer() override = default;

public:
    void SetData() {}
    void GetData() {}

public:
    uint32_t GetSize() const { return _desc.Size; }
    uint32_t GetStride() const { return _desc.Stride; }
    uint32_t GetElementsCount() const { return _desc.Size / _desc.Stride; }

    GPUPixelFormat GetFormat() const { return _desc.Format; }
    GPUResourceUsage GetUsage() const { return _desc.Usage; }
    GPUBufferUtility GetUtility() const { return _desc.Utility; }
    GPUBufferDescription GetDescription() const { return _desc; }

protected:
    GPUBufferDescription _desc;
};
}

#endif