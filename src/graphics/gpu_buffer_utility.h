#ifndef _GPU_BUFFER_UTILITY_
#define _GPU_BUFFER_UTILITY_

#include <cstdint>

namespace Quack {
enum class GPUBufferUtility : uint32_t {
    Unknown,
    IndexBuffer,
    VertexBuffer
};
}
#endif