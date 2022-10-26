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
//     void Resize(float, float) override {}
//     void Invalidate() override {}

//     void Bind() const override {}
//     void Unbind() const override {}

// public:
//     const std::vector<VkImage>& GetImages() const;
//     const std::vector<VkImageView>& GetViews() const;
//     const std::vector<VkFramebuffer>& GetFramebuffers() const;

// private:
//     void CreateImageViews();
//     void CreateFramebuffers();

// private:
//     std::vector<VkImage> _swapChainImages;
//     std::vector<VkImageView> _swapChainImageViews;
//     std::vector<VkFramebuffer> _swapChainFramebuffers;
// };
// }

// #endif