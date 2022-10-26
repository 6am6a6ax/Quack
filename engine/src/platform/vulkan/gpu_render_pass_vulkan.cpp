// #include "quack/core/application.h"
// #include "quack/quack.h"
// #include <stdexcept>
// #include <vulkan/vulkan_core.h>

// Quack::GPURenderPassVulkan::GPURenderPassVulkan(const GPURenderPassDescription& desc)
//     : Quack::GPURenderPass(desc)
//     , _colorAttachmentDescription({})
//     , _colorAttachmentReference({})
//     , _subpassDescription({})
//     , _subpassDependency({})
//     , _renderPass(VK_NULL_HANDLE)
//     , _renderPassInfo({})
// {
//     Init();
//     Create();   
// }

// Quack::GPURenderPassVulkan::~GPURenderPassVulkan() {
//     const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
//     vkDestroyRenderPass(device->GetDevice(), _renderPass, nullptr);
// }

// void Quack::GPURenderPassVulkan::Init() {
//     InitColorAttachmentDescription();
//     InitColorAttachmentReference();
//     InitSubpassDescription();
//     InitSubpassDependency();
//     InitRenderPass();
// }

// void Quack::GPURenderPassVulkan::Create() {
//     CreateRenderPass();
// }

// void Quack::GPURenderPassVulkan::InitColorAttachmentDescription() {
//     const auto& swapChain = dynamic_cast<GPUSwapChainVulkan*>(_desc.SwapChain);

//     _colorAttachmentDescription.format = swapChain->getSwapChainImageFormat();

//     _colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;

//     _colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//     _colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

//     _colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//     _colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

//     _colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//     _colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
// }

// void Quack::GPURenderPassVulkan::InitColorAttachmentReference() {
//     _colorAttachmentReference.attachment = 0;
//     _colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
// }

// void Quack::GPURenderPassVulkan::InitSubpassDescription() {
//     _subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

//     _subpassDescription.colorAttachmentCount = 1;
//     _subpassDescription.pColorAttachments = &_colorAttachmentReference;
// }

// void Quack::GPURenderPassVulkan::InitSubpassDependency() {
//     _subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
//     _subpassDependency.dstSubpass = 0;

//     _subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//     _subpassDependency.srcAccessMask = 0;

//     _subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//     _subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
// }

// void Quack::GPURenderPassVulkan::InitRenderPass() {
//     _renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

//     _renderPassInfo.attachmentCount = 1;
//     _renderPassInfo.pAttachments = &_colorAttachmentDescription;

//     _renderPassInfo.subpassCount = 1;
//     _renderPassInfo.pSubpasses = &_subpassDescription;
//     _renderPassInfo.dependencyCount = 1;
//     _renderPassInfo.pDependencies = &_subpassDependency;
// }

// void Quack::GPURenderPassVulkan::CreateRenderPass() {
//     const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
//     if (vkCreateRenderPass(device->GetDevice(), &_renderPassInfo, nullptr, &_renderPass) != VK_SUCCESS) {
//         throw std::runtime_error("Failed to create render pass!");
//     }
// }

// const VkRenderPass& Quack::GPURenderPassVulkan::GetRenderPass() const {
//     return _renderPass;
// }

// void Quack::GPURenderPassVulkan::Begin(Quack::GPUSwapChainVulkan* swapChain, uint32_t index) {

//     VkRenderPassBeginInfo info{};
//     info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//     info.renderPass = _renderPass;

//     info.framebuffer = swapChain->getFrameBuffer(index);
//     info.renderArea.offset = {0, 0};
//     info.renderArea.extent = swapChain->getSwapChainExtent();

//     VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
//     info.clearValueCount = 1;
//     info.pClearValues = &clearColor;

//     const auto& commandBuffer = dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer);
//     vkCmdBeginRenderPass(commandBuffer->GetCommandBuffer(), &info, VK_SUBPASS_CONTENTS_INLINE);
// }

// void Quack::GPURenderPassVulkan::End() {
//     const auto& commandBuffer = dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer);
//     vkCmdEndRenderPass(commandBuffer->GetCommandBuffer());
// }