#ifndef QUACK_GPU_DEVICE_VULKAN_H
#define QUACK_GPU_DEVICE_VULKAN_H

#include <vulkan/vulkan_core.h>
#include "quack/graphics/gpu_device.h"

namespace Quack {
class GPUDeviceVulkan final : public GPUDevice {
public:
    explicit GPUDeviceVulkan(const GPUDeviceDescription&);
    ~GPUDeviceVulkan() override;

public:
    std::shared_ptr<GPUSwapChain> CreateSwapChain(const GPUSwapChainDescription &) const override;
    std::shared_ptr<GPUShaderProgram> CreateShaderProgram(const GPUShaderProgramDescription &) const override;
    // std::shared_ptr<GPUFramebuffer> CreateFramebuffer(const GPUFramebufferDescription &) const override;

public:
    VkDevice GetDeviceHandle() const;

    VkQueue GetGraphicsQueue() const;
    VkQueue GetPresentQueue() const;

private:
    VkDevice _device;

    VkQueue _graphicsQueue;
    VkQueue _presentQueue;
};
}

#endif