#ifndef QUACK_GPU_SWAP_CHAIN_VULKAN_H
#define QUACK_GPU_SWAP_CHAIN_VULKAN_H

#include <vulkan/vulkan_core.h>
#include "quack/graphics/gpu_swap_chain.h"

namespace Quack {
class GPUSwapChainVulkan final : public GPUSwapChain
{
public:
    explicit GPUSwapChainVulkan(const GPUSwapChainDescription&);
    ~GPUSwapChainVulkan() override;

public:
    void DrawFrame();

    void BeginFrame();
    void EndFrame();
    
public:
    VkSwapchainKHR GetSwapChain() const;
    VkFormat GetSwapChainImageFormat() const;
    const VkExtent2D& GetSwapChainExtent() const;
    const std::vector<VkImage>& GetSwapChainImages() const;

private:
    void CreateSwapChain();
    void CreateImageViews(); 
    void CreateRenderPass();
    void CreateGraphicsPipeline();
    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateCommandBuffer();
    void CreateSyncObjects();

    void RecordCommandBuffer();

private:
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

private:
    VkSwapchainKHR _swapChain;

    VkFormat _swapChainImageFormat;
    VkExtent2D _swapChainExtent;

    std::vector<VkImage> _swapChainImages;
    std::vector<VkImageView> _swapChainImageViews;
    std::vector<VkFramebuffer> _swapChainFramebuffers;

    VkRenderPass _renderPass;

    VkPipelineLayout _pipelineLayout;
    VkPipeline _graphicsPipeline;

    VkCommandPool _commandPool;
    VkCommandBuffer _commandBuffer;

    VkSemaphore _imageAvailableSemaphore;
    VkSemaphore _renderFinishedSemaphore;
    VkFence _inFlightFence;

    uint32_t _currentImageIndex;
};
}

#endif