#ifndef QUACK_GPU_DEVICE_VULKAN_H
#define QUACK_GPU_DEVICE_VULKAN_H

#include <vulkan/vulkan_core.h>

#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_swap_chain.h"
#include "quack/graphics/gpu_shader_program.h"

namespace Quack {
class GPUDeviceVulkan final : public GPUDevice {
public:
    GPUDeviceVulkan(const GPUDeviceDescription&);
    ~GPUDeviceVulkan() override = default;

public:
    std::shared_ptr<GPUSwapChain> CreateSwapChain(const GPUSwapChainDescription &) const override;
    std::shared_ptr<GPUFramebuffer> CreateFramebuffer(const GPUFramebufferDescription &) const override;
    std::shared_ptr<GPUShaderProgram> CreateShaderProgram(const GPUShaderProgramDescription &) const override;

public:
    VkDevice GetDevice() const;

    const VkQueue& GetGraphicsQueue() const;
    const VkQueue& GetPresentQueue() const;

private:
    VkDevice _device;

    VkQueue _graphicsQueue;
    VkQueue _presentQueue;
};
}

#endif