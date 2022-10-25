#ifndef QUACK_GPU_SWAP_CHAIN_VULKAN_H
#define QUACK_GPU_SWAP_CHAIN_VULKAN_H

#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_swap_chain.h"

#include "quack/platform/vulkan/gpu_adapter_vulkan.h"
#include "quack/platform/vulkan/gpu_device_vulkan.h"
#include "quack/platform/vulkan/gpu_context_vulkan.h"

#include <vulkan/vulkan.h>

#include <memory>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Quack {
class GPUSwapChainVulkan final : public GPUSwapChain {
 public:
  static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    GPUSwapChainVulkan(const GPUSwapChainDescription& desc);

    // GPUSwapChainVulkan(Quack::GPUDeviceVulkan &deviceRef, VkExtent2D windowExtent);
//   LveSwapChain(
//       LveDevice &deviceRef, VkExtent2D windowExtent, std::shared_ptr<LveSwapChain> previous);

  ~GPUSwapChainVulkan() override;

  GPUSwapChainVulkan(const GPUSwapChainVulkan &) = delete;
  GPUSwapChainVulkan &operator=(const GPUSwapChainVulkan &) = delete;

  VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
  VkRenderPass getRenderPass() { return renderPass; }
  VkImageView getImageView(int index) { return swapChainImageViews[index]; }
  size_t imageCount() { return swapChainImages.size(); }
  VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
  VkExtent2D getSwapChainExtent() { return swapChainExtent; }
  uint32_t width() { return swapChainExtent.width; }
  uint32_t height() { return swapChainExtent.height; }

  float extentAspectRatio() {
    return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
  }
  VkFormat findDepthFormat();

  VkResult acquireNextImage(uint32_t *imageIndex);
  VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

  bool compareSwapFormats(const GPUSwapChainVulkan &swapChain) const {
    return swapChain.swapChainDepthFormat == swapChainDepthFormat &&
           swapChain.swapChainImageFormat == swapChainImageFormat;
  }

  void Draw();

 private:
  void init();
  void createSwapChain();
  void createImageViews();
  void createDepthResources();
  void createRenderPass();
  void createFramebuffers();
  void createSyncObjects();

  // Helper functions
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

  VkFormat swapChainImageFormat;
  VkFormat swapChainDepthFormat;
  VkExtent2D swapChainExtent;

  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkRenderPass renderPass;

  std::vector<VkImage> depthImages;
  std::vector<VkImageView> depthImageViews;
  std::vector<VkDeviceMemory> depthImageMemorys;

  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;

//   GPUDeviceVulkan &device;
//   VkExtent2D windowExtent;

  VkSwapchainKHR swapChain;

//   std::shared_ptr<GPUSwapChainVulkan> oldSwapChain;

  VkSemaphore imageAvailableSemaphore;
  VkSemaphore renderFinishedSemaphore;
  VkFence inFlightFence;
  VkFence imagesInFlight;
  size_t currentFrame = 0;

  VkSurfaceKHR surface = VK_NULL_HANDLE;

  GPUDeviceVulkan* device;
  GPUContextVulkan* context;
  GPUAdapterVulkan* adapter;
};}

#endif