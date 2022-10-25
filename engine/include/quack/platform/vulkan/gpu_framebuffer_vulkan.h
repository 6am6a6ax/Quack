// #ifndef QUACK_GPU_FRAMEBUFFER_VULKAN_H
// #define QUACK_GPU_FRAMEBUFFER_VULKAN_H

// #include "quack/graphics/gpu_framebuffer.h"
// #include <vector>
// #include <vulkan/vulkan_core.h>

// namespace Quack {
// class GPUFramebufferVulkan final : public GPUFramebuffer {
// public:
//     using SwapChain = std::vector<VkFramebuffer>;

// public:
//     explicit GPUFramebufferVulkan(const GPUFramebufferDescription&);
//     ~GPUFramebufferVulkan() override;

// public:
//     void Resize(float, float) override;
//     void Invalidate() override;

//     void Bind() const override;
//     void Unbind() const override;

// public:
//     SwapChain GetSwapChain() const { return _swapChain; }

// private:
//     void InitAndCreate();

//     VkFramebufferCreateInfo InitSingleFramebuffer(VkRenderPass, VkImageView, VkExtent2D);
//     void CreateSingleFramebuffer(VkDevice, VkFramebufferCreateInfo, VkFramebuffer&);

// private:
//     SwapChain _swapChain;
// };
// }

// #endif