#ifndef _GPU_BUFFER_DESCRIPTION_
#define _GPU_BUFFER_DESCRIPTION_

#include <cstdint>

#include "gpu_buffer_utility.hpp"
#include "gpu_pixel_format.hpp"
#include "gpu_resource_usage.hpp"

namespace Quack {
struct GPUBufferDescription {
    uint32_t Size;
    uint32_t Stride;

    GPUPixelFormat Format;
    GPUBufferUtility Utility;
    GPUResourceUsage Usage;
};
}

#endif