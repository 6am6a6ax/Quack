#ifndef QUAKC_GPU_SWAP_CHAIN_H
#define QUAKC_GPU_SWAP_CHAIN_H

#include "quack/graphics/gpu_adapter.h"
#include "quack/graphics/gpu_context.h"
#include "quack/graphics/gpu_device.h"
#include <vulkan/vulkan_core.h>

namespace Quack {
class GPUDevice;
class GPUAdapter;
class GPUContext;

struct GPUSwapChainDescription {
    GPUCommandBuffer* CommandBuffer;
    GPUContext* Context;
    GPUAdapter* Adapter;
    GPUDevice* Device;
};

class GPUSwapChain {
public:
    GPUSwapChain(const GPUSwapChainDescription& desc) : _desc(desc) {}
    virtual ~GPUSwapChain() = default;

public:
    const GPUSwapChainDescription& GetDescription() const { return _desc; }
    GPUCommandBuffer* GetCommandBuffer() const { return _desc.CommandBuffer; }

    GPUContext* GetContext() const { _desc.Context; }
    GPUAdapter* GetAdapter() const { _desc.Adapter; }
    GPUDevice* GetDevice() const { _desc.Device; }

protected:
    GPUSwapChainDescription _desc;
};
}

#endif