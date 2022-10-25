#include "quack/quack.h"

// Quack::GPUSwapChainVulkan::GPUSwapChainVulkan(Quack::GPUDeviceVulkan &deviceRef, VkExtent2D extent)
//     : device{deviceRef}, windowExtent{extent} {
//   init();
// }

Quack::GPUSwapChainVulkan::GPUSwapChainVulkan(const Quack::GPUSwapChainDescription& desc) 
    : Quack::GPUSwapChain(desc)
    , device(nullptr)
    , context(nullptr)
    , adapter(nullptr)     
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
  createRenderPass();
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

void Quack::GPUSwapChainVulkan::createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(device->GetDevice(), &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
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
        framebufferInfo.renderPass = renderPass;
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

void Quack::GPUSwapChainVulkan::createDepthResources() {
  VkFormat depthFormat = findDepthFormat();
  swapChainDepthFormat = depthFormat;
  VkExtent2D swapChainExtent = getSwapChainExtent();

  depthImages.resize(imageCount());
  depthImageMemorys.resize(imageCount());
  depthImageViews.resize(imageCount());

  for (int i = 0; i < depthImages.size(); i++) {
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = swapChainExtent.width;
    imageInfo.extent.height = swapChainExtent.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = depthFormat;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.flags = 0;

    // device->CreateImageWithInfo(
    //     imageInfo,
    //     VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    //     depthImages[i],
    //     depthImageMemorys[i]);

    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = depthImages[i];
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = depthFormat;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(device->GetDevice(), &viewInfo, nullptr, &depthImageViews[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to create texture image view!");
    }
  }
}

void Quack::GPUSwapChainVulkan::createSyncObjects() {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);

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
  const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);

    vkWaitForFences(device->GetDevice(), 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkResetFences(device->GetDevice(), 1, &inFlightFence);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(device->GetDevice(), swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    const auto& commandBuffer = dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer);

    vkResetCommandBuffer(commandBuffer->GetCommandBuffer(), /*VkCommandBufferResetFlagBits*/ 0);


  // record CommandBUffer

  


    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer->GetCommandBuffer();

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

  // const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);

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
