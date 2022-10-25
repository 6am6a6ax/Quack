#include "quack/quack.h"
#include <vulkan/vulkan_core.h>

Quack::GPUFramebufferVulkan::GPUFramebufferVulkan(const Quack::GPUFramebufferDescription& desc)
    : Quack::GPUFramebuffer(desc)
    , _swapChain({})
{
    InitAndCreate();
}

Quack::GPUFramebufferVulkan::~GPUFramebufferVulkan() {
    const auto& context = dynamic_cast<GPUContextVulkan*>(Application::GetInstance().GetContext());
    for (auto& framebuffer : _swapChain) {
 //       vkDestroyFramebuffer(context->GetDevice(), framebuffer, nullptr);
    }
}

void Quack::GPUFramebufferVulkan::InitAndCreate() {
    const auto& context = dynamic_cast<GPUContextVulkan*>(Application::GetInstance().GetContext());
    const auto& swapChainImageViews = context->GetSwapChainImageViews();
    _swapChain.resize(swapChainImageViews.size());
    for(size_t i = 0; i < _swapChain.size(); i++) {
        VkFramebufferCreateInfo framebufferCreateInfo = InitSingleFramebuffer(
            dynamic_cast<GPURenderPassVulkan*>(GetRenderPass())->GetRenderPass(),
            swapChainImageViews[i],
            context->GetExtent2D()
        );
   //     CreateSingleFramebuffer(context->GetDevice(), framebufferCreateInfo, _swapChain[i]);
    }
}

VkFramebufferCreateInfo Quack::GPUFramebufferVulkan::InitSingleFramebuffer(VkRenderPass renderPass, 
                                                                           VkImageView swapChainImageView,
                                                                           VkExtent2D swapChainExtent) 
{
    VkImageView attachments[] = { swapChainImageView };

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = swapChainExtent.width;
    framebufferInfo.height = swapChainExtent.height;
    framebufferInfo.layers = 1; 
    
    return framebufferInfo;
}

void Quack::GPUFramebufferVulkan::CreateSingleFramebuffer(VkDevice device, 
                                                          VkFramebufferCreateInfo framebufferInfo, 
                                                          VkFramebuffer& framebuffer) 
{
    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create framebuffer!");
    }
}