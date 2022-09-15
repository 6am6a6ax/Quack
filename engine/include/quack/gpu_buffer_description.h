#ifndef GPU_BUFFER_DESCRIPTION_H
#define GPU_BUFFER_DESCRIPTION_H

#include <cstdint>

#include "gpu_pixel_format.h"
#include "gpu_resource_usage.h"
#include "gpu_buffer_utility.h"

namespace Quack {
struct GPUBufferDescription {
    uint32_t Size;
    uint32_t Stride;

    GPUPixelFormat Format;
    GPUResourceUsage Usage;
    GPUBufferUtility Utility;
};
}

#endif