#ifndef _GPU_BUFFER_
#define _GPU_BUFFER_

#include <cstdint>

#include "gpu_pixel_format.hpp"
#include "gpu_buffer_utility.hpp"
#include "gpu_buffer_description.hpp"

namespace Quack {
class GPUBuffer {
public:
    virtual ~GPUBuffer() {}

public:
    void SetData() {}
    void GetData() {}

public:
    uint32_t GetSize() const {}
    uint32_t GetStride() const {}
    GPUPixelFormat GetFormat() const {}
    uint32_t GetElementsCount() const {}
    GPUBufferUtility GetUtility() const {}
    GPUBufferDescription GetDescription() const {}
};
}

#endif