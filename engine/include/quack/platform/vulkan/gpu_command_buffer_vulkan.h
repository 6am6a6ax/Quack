#ifndef QUACK_GPU_COMMAND_BUFFER_VULKAN_H
#define QUACK_GPU_COMMAND_BUFFER_VULKAN_H

#include "quack/graphics/gpu_command_buffer.h"
#include <vulkan/vulkan_core.h>

namespace Quack {
class GPUCommandBufferVulkan final : public GPUCommandBuffer {
public:
    GPUCommandBufferVulkan(const GPUCommandBufferDescription& desc);
    ~GPUCommandBufferVulkan() override;

public:
    void Begin();
    void End();

    void Reset();

public:
    const VkCommandPool& GetCommandPool() const;
    const VkCommandBuffer& GetCommandBuffer() const;

private:
    void Init();
    void Create();

private:
    void InitCommandPool();
    void CreateCommandPool();

    void InitCommandBuffer();
    void CreateCommandBuffer();

private:
    VkCommandPool _commandPool;
    VkCommandPoolCreateInfo _commandPoolCreateInfo;

    VkCommandBuffer _commandBuffer;
    VkCommandBufferAllocateInfo _commandBufferAllocateInfo;
};
}

#endif