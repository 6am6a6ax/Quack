#ifndef GPU_BUFFER_H
#define GPU_BUFFER_H

#include <cstdint>

#include "gpu_resource.h"
#include "gpu_pixel_format.h"
#include "gpu_buffer_utility.h"
#include "gpu_resource_usage.h"
#include "gpu_buffer_description.h"

namespace Quack {
class GPUBuffer : public GPUResource {
public:
    GPUBuffer();
    explicit GPUBuffer(GPUBufferDescription desc);

    GPUBuffer(const GPUBuffer &);
    GPUBuffer(GPUBuffer &&) noexcept;

    GPUBuffer & operator=(const GPUBuffer &);
    GPUBuffer & operator=(GPUBuffer &&) noexcept;

public:
    ~GPUBuffer() override;

public:
    const uint32_t & GetSize() const;
    const uint32_t & GetStride() const;
    const uint32_t GetElementsCount() const;

    const GPUPixelFormat & GetFormat() const;
    const GPUResourceUsage & GetUsage() const;
    const GPUBufferUtility & GetUtility() const;
    const GPUBufferDescription & GetDescription() const;

protected:
    GPUBufferDescription _desc;
};
}

#endif