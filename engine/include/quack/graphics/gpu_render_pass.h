#ifndef QUACK_GPU_RENDER_PASS_H
#define QUACK_GPU_RENDER_PASS_H

#include "quack/graphics/gpu_framebuffer.h"
#include "quack/graphics/gpu_command_buffer.h"

namespace Quack {
class GPUFramebuffer;
class GPUCommandBuffer;

class GPUDevice;
class GPUContext;

class GPUSwapChain;

class GPUCommandBuffer;

struct GPURenderPassDescription {
    // GPUFramebuffer* Framebuffer;
    // GPUCommandBuffer* CommandBuffer;

    GPUContext* Context;
    GPUDevice* Device;

    GPUSwapChain* SwapChain;

    GPUCommandBuffer* CommandBuffer;
};

class GPURenderPass {
public:
    GPURenderPass(const GPURenderPassDescription& desc) : _desc(desc) {}
    virtual ~GPURenderPass() = default;

public:
    const GPURenderPassDescription& GetDescription() const { return _desc; }
    
protected:
    GPURenderPassDescription _desc;
};
}

#endif