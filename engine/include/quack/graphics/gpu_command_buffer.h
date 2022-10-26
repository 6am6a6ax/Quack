#ifndef QUACK_GPU_COMMAND_BUFFER_H
#define QUACK_GPU_COMMAND_BUFFER_H

#include "quack/graphics/gpu_device.h"

namespace Quack {
class GPUContext;
class GPUDevice;

struct GPUCommandBufferDescription {
    GPUContext* Context;
    GPUDevice* Device;
    GPUAdapter* Adapter;
};

class GPUCommandBuffer {
public:
    GPUCommandBuffer(const GPUCommandBufferDescription& desc) : _desc(desc) {}
    virtual ~GPUCommandBuffer() = default;

public:
    const GPUCommandBufferDescription& GetDescription() { return _desc; }

protected:
    GPUCommandBufferDescription _desc;
};
}

#endif