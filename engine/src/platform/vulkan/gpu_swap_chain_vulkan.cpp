#include "quack/quack.h"
#include <cstdint>
#include <vulkan/vulkan_core.h>

// Quack::GPUSwapChainVulkan::GPUSwapChainVulkan(Quack::GPUDeviceVulkan &deviceRef, VkExtent2D extent)
//     : device{deviceRef}, windowExtent{extent} {
//   init();
// }

Quack::GPUSwapChainVulkan::GPUSwapChainVulkan(const Quack::GPUSwapChainDescription& desc) 
    : Quack::GPUSwapChain(desc)
    , imageIndex(0)
    , swapChainImages({})
    , swapChainImageViews({})
    , swapChainFramebuffers({})
    , swapChain(VK_NULL_HANDLE)
    , imageAvailableSemaphore(VK_NULL_HANDLE)
    , renderFinishedSemaphore(VK_NULL_HANDLE)
    , inFlightFence(VK_NULL_HANDLE)
    , device(nullptr)
    , context(nullptr)
    , adapter(nullptr)
    , _colorAttachmentDescription({})
    , _colorAttachmentReference({})
    , _subpassDescription({})
    , _subpassDependency({})
    , _renderPass(VK_NULL_HANDLE)
    , _renderPassInfo({})     
{
    init();
}

// GPUSwapChainVulkan::GPUSwapChainVulkan(
//     LveDevice &deviceRef, VkExtent2D extent, std::shared_ptr<GPUSwapChainVulkan> previous)
//     : device{deviceRef}, windowExtent{extent}, oldSwapChain{previous} {
//   init();
//   oldSwapChain = nullptr;
// }

void Quack::GPUSwapChainVulkan::init() {
  device = reinterpret_cast<GPUDeviceVulkan*>(_desc.Device);
  context = reinterpret_cast<GPUContextVulkan*>(_desc.Context);
  adapter = reinterpret_cast<GPUAdapterVulkan*>(_desc.Adapter);


  createSwapChain();
  createImageViews();
  InitRenderPassMain();
  CreateRenderPass();
  // createDepthResources();
  createFramebuffers();
  createSyncObjects();
}

Quack::GPUSwapChainVulkan::~GPUSwapChainVulkan() {
  // for (auto imageView : swapChainImageViews) {
  //   vkDestroyImageView(device->GetDevice(), imageView, nullptr);
  // }
  // swapChainImageViews.clear();

  // if (swapChain != nullptr) {
  //   vkDestroySwapchainKHR(device->GetDevice(), swapChain, nullptr);
  //   swapChain = nullptr;
  // }

  // for (int i = 0; i < depthImages.size(); i++) {
  //   vkDestroyImageView(device->GetDevice(), depthImageViews[i], nullptr);
  //   vkDestroyImage(device->GetDevice(), depthImages[i], nullptr);
  //   vkFreeMemory(device->GetDevice(), depthImageMemorys[i], nullptr);
  // }

  // for (auto framebuffer : swapChainFramebuffers) {
  //   vkDestroyFramebuffer(device->GetDevice(), framebuffer, nullptr);
  // }

  // vkDestroyRenderPass(device->GetDevice(), renderPass, nullptr);

  // // cleanup synchronization objects
  // for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
  //   vkDestroySemaphore(device->GetDevice(), renderFinishedSemaphores[i], nullptr);
  //   vkDestroySemaphore(device->GetDevice(), imageAvailableSemaphores[i], nullptr);
  //   vkDestroyFence(device->GetDevice(), inFlightFences[i], nullptr);
  // }
}

// VkResult Quack::GPUSwapChainVulkan::acquireNextImage(uint32_t *imageIndex) {
//   vkWaitForFences(
//       device->GetDevice(),
//       1,
//       &inFlightFences[currentFrame],
//       VK_TRUE,
//       std::numeric_limits<uint64_t>::max());

//   VkResult result = vkAcquireNextImageKHR(
//       device->GetDevice(),
//       swapChain,
//       std::numeric_limits<uint64_t>::max(),
//       imageAvailableSemaphores[currentFrame],  // must be a not signaled semaphore
//       VK_NULL_HANDLE,
//       imageIndex);

//   return result;
// }

// VkResult Quack::GPUSwapChainVulkan::submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex) {
//   if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE) {
//     vkWaitForFences(device->GetDevice(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);
//   }
//   imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

//   VkSubmitInfo submitInfo = {};
//   submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

//   VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
//   VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
//   submitInfo.waitSemaphoreCount = 1;
//   submitInfo.pWaitSemaphores = waitSemaphores;
//   submitInfo.pWaitDstStageMask = waitStages;

//   submitInfo.commandBufferCount = 1;
//   submitInfo.pCommandBuffers = buffers;

//   VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
//   submitInfo.signalSemaphoreCount = 1;
//   submitInfo.pSignalSemaphores = signalSemaphores;

//   vkResetFences(device->GetDevice(), 1, &inFlightFences[currentFrame]);
//   if (vkQueueSubmit(device->GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) !=
//       VK_SUCCESS) {
//     throw std::runtime_error("failed to submit draw command buffer!");
//   }

//   VkPresentInfoKHR presentInfo = {};
//   presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

//   presentInfo.waitSemaphoreCount = 1;
//   presentInfo.pWaitSemaphores = signalSemaphores;

//   VkSwapchainKHR swapChains[] = {swapChain};
//   presentInfo.swapchainCount = 1;
//   presentInfo.pSwapchains = swapChains;

//   presentInfo.pImageIndices = imageIndex;

//   auto result = vkQueuePresentKHR(device->GetPresentQueue(), &presentInfo);

//   currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

//   return result;
// }

void Quack::GPUSwapChainVulkan::createSwapChain() {
    SwapChainSupportDetails swapChainSupport = 
      GPUAdapterVulkan::FindQuerySwapChainSupport(adapter->GetAdapter(), context->GetSurface());

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.SurfaceForamts);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.PresentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.SurfaceCapabilities);

    uint32_t imageCount = swapChainSupport.SurfaceCapabilities.minImageCount + 1;
    if (swapChainSupport.SurfaceCapabilities.maxImageCount > 0 && imageCount > swapChainSupport.SurfaceCapabilities.maxImageCount) {
        imageCount = swapChainSupport.SurfaceCapabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = context->GetSurface();

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = GPUAdapterVulkan::FindQueueFamiliesIndices(adapter->GetAdapter(), context->GetSurface());

    uint32_t queueFamilyIndices[] = {indices.GraphicsFamily.value(), indices.PresentFamily.value()};

    if (indices.GraphicsFamily != indices.PresentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = swapChainSupport.SurfaceCapabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(device->GetDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(device->GetDevice(), swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device->GetDevice(), swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;
}

void Quack::GPUSwapChainVulkan::createImageViews() {
    swapChainImageViews.resize(swapChainImages.size());
    for (size_t i = 0; i < swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = swapChainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device->GetDevice(), &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void Quack::GPUSwapChainVulkan::createFramebuffers() {
    swapChainFramebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
        VkImageView attachments[] = {
            swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = _renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device->GetDevice(), &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void Quack::GPUSwapChainVulkan::createSyncObjects() {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(device->GetDevice(), &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }
}

VkSurfaceFormatKHR Quack::GPUSwapChainVulkan::chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR> &availableFormats) {
  for (const auto &availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
        availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return availableFormat;
    }
  }

  return availableFormats[0];
}

VkPresentModeKHR Quack::GPUSwapChainVulkan::chooseSwapPresentMode(
    const std::vector<VkPresentModeKHR> &availablePresentModes) {
  for (const auto &availablePresentMode : availablePresentModes) {
    if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
      std::cout << "Present mode: Mailbox" << std::endl;
      return availablePresentMode;
    }
  }

  // for (const auto &availablePresentMode : availablePresentModes) {
  //   if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
  //     std::cout << "Present mode: Immediate" << std::endl;
  //     return availablePresentMode;
  //   }
  // }

  std::cout << "Present mode: V-Sync" << std::endl;
  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Quack::GPUSwapChainVulkan::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) {
  if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    // VkExtent2D actualExtent = windowExtent;
    // actualExtent.width = std::max(
    //     capabilities.minImageExtent.width,
    //     std::min(capabilities.maxImageExtent.width, actualExtent.width));
    // actualExtent.height = std::max(
    //     capabilities.minImageExtent.height,
    //     std::min(capabilities.maxImageExtent.height, actualExtent.height));

    // return actualExtent;
  }
}

VkFormat Quack::GPUSwapChainVulkan::findDepthFormat() {
  return adapter->FindSupportedFormat(
      {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
      VK_IMAGE_TILING_OPTIMAL,
      VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

void Quack::GPUSwapChainVulkan::Draw() {

}


void Quack::GPUSwapChainVulkan::Begin() {
    vkWaitForFences(device->GetDevice(), 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkResetFences(device->GetDevice(), 1, &inFlightFence);

    imageIndex = 0;
    vkAcquireNextImageKHR(device->GetDevice(), swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
}

void Quack::GPUSwapChainVulkan::End() {
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    const auto& commandBuffer = dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer);
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer->GetCommandBuffer();

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(device->GetGraphicsQueue(), 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(device->GetPresentQueue(), &presentInfo);
}








void Quack::GPUSwapChainVulkan::InitRenderPassMain() {
    InitColorAttachmentDescription();
    InitColorAttachmentReference();
    InitSubpassDescription();
    InitSubpassDependency();
    InitRenderPass();
}

void Quack::GPUSwapChainVulkan::InitColorAttachmentDescription() {
    _colorAttachmentDescription.format = getSwapChainImageFormat();

    _colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;

    _colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    _colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

    _colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    _colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    _colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    _colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
}

void Quack::GPUSwapChainVulkan::InitColorAttachmentReference() {
    _colorAttachmentReference.attachment = 0;
    _colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}

void Quack::GPUSwapChainVulkan::InitSubpassDescription() {
    _subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    _subpassDescription.colorAttachmentCount = 1;
    _subpassDescription.pColorAttachments = &_colorAttachmentReference;
}

void Quack::GPUSwapChainVulkan::InitSubpassDependency() {
    _subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    _subpassDependency.dstSubpass = 0;

    _subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    _subpassDependency.srcAccessMask = 0;

    _subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    _subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
}

void Quack::GPUSwapChainVulkan::InitRenderPass() {
    _renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

    _renderPassInfo.attachmentCount = 1;
    _renderPassInfo.pAttachments = &_colorAttachmentDescription;

    _renderPassInfo.subpassCount = 1;
    _renderPassInfo.pSubpasses = &_subpassDescription;
    _renderPassInfo.dependencyCount = 1;
    _renderPassInfo.pDependencies = &_subpassDependency;
}

void Quack::GPUSwapChainVulkan::CreateRenderPass() {
    if (vkCreateRenderPass(device->GetDevice(), &_renderPassInfo, nullptr, &_renderPass) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create render pass!");
    }
}

const VkRenderPass& Quack::GPUSwapChainVulkan::GetRenderPass() const {
    return _renderPass;
}

void Quack::GPUSwapChainVulkan::BeginRenderPass() {

    VkRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.renderPass = _renderPass;

    info.framebuffer = getFrameBuffer(GetImageIndex());
    info.renderArea.offset = {0, 0};
    info.renderArea.extent = getSwapChainExtent();

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    info.clearValueCount = 1;
    info.pClearValues = &clearColor;

    const auto& commandBuffer = dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer);
    vkCmdBeginRenderPass(commandBuffer->GetCommandBuffer(), &info, VK_SUBPASS_CONTENTS_INLINE);
}

void Quack::GPUSwapChainVulkan::EndRenderPass() {
    const auto& commandBuffer = dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer);
    vkCmdEndRenderPass(commandBuffer->GetCommandBuffer());
}