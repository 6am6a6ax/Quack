#ifndef QUACK_GPU_VERTEX_ARRAY_H
#define QUACK_GPU_VERTEX_ARRAY_H

#include <memory>

#include "gpu_buffer.h"
#include "gpu_resource.h"

namespace Quack {
class GPUVertexArray : public GPUResource {
public:
    virtual ~GPUVertexArray() = default;

public:
    virtual void AddBuffer(std::shared_ptr<GPUBuffer>) = 0;

private:
    virtual void SetBufferLayout(const GPUBuffer::Layout &) = 0;
};
}

#endif
