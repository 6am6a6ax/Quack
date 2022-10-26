// #include "quack/quack.h"
// #include <vulkan/vulkan_core.h>

// Quack::GPUFramebufferVulkan::GPUFramebufferVulkan(const Quack::GPUFramebufferDescription& desc)
//     : Quack::GPUFramebuffer(desc)
//     , _swapChain({})
// {
//     CreateImageViews();
//     CreateFramebuffers();
// }

// Quack::GPUFramebufferVulkan::~GPUFramebufferVulkan() {

// }

// void Quack::GPUFramebufferVulkan::CreateImageViews() {
//     _swapChainImageViews.resize(_swapChainImages.size());
//     for (size_t i = 0; i < _swapChainImages.size(); i++) {
//         VkImageViewCreateInfo createInfo{};
//         createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
//         createInfo.image = _swapChainImages[i];
//         createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
//         createInfo.format = swapChainImageFormat;
//         createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
//         createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
//         createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
//         createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
//         createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
//         createInfo.subresourceRange.baseMipLevel = 0;
//         createInfo.subresourceRange.levelCount = 1;
//         createInfo.subresourceRange.baseArrayLayer = 0;
//         createInfo.subresourceRange.layerCount = 1;

//         if (vkCreateImageView(device->GetDevice(), &createInfo, nullptr, &_swapChainImageViews[i]) != VK_SUCCESS) {
//             throw std::runtime_error("failed to create image views!");
//         }
//     }
// }

// void Quack::GPUFramebufferVulkan::CreateFramebuffers() {
//     swapChainFramebuffers.resize(swapChainImageViews.size());

//     for (size_t i = 0; i < swapChainImageViews.size(); i++) {
//         VkImageView attachments[] = {
//             swapChainImageViews[i]
//         };

//         VkFramebufferCreateInfo framebufferInfo{};
//         framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
//         framebufferInfo.renderPass = dynamic_cast<GPURenderPassVulkan*>(_desc.RenderPass)->GetRenderPass();
//         framebufferInfo.attachmentCount = 1;
//         framebufferInfo.pAttachments = attachments;
//         framebufferInfo.width = swapChainExtent.width;
//         framebufferInfo.height = swapChainExtent.height;
//         framebufferInfo.layers = 1;

//         if (vkCreateFramebuffer(device->GetDevice(), &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
//             throw std::runtime_error("failed to create framebuffer!");
//         }
//     }
// }