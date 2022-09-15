#ifndef GPU_BUFFER_UTILITY_H
#define GPU_BUFFER_UTILITY_H

#include <cstdint>

namespace Quack {
enum class GPUBufferUtility : uint32_t {
    Unknown,
    IndexBuffer,
    VertexBuffer
};
}
#endif