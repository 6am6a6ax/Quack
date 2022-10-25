#include "quack/graphics/gpu_render_pass.h"
#include "quack/quack.h"
#include <stdexcept>
#include <vulkan/vulkan_core.h>

Quack::GPUCommandBufferVulkan::GPUCommandBufferVulkan(const Quack::GPUCommandBufferDescription& desc)
    : Quack::GPUCommandBuffer(desc) 
    , _commandPool(VK_NULL_HANDLE)
    , _commandBuffer(VK_NULL_HANDLE)
{
    Init();
    Create();
}

void Quack::GPUCommandBufferVulkan::Init() {
    InitCommandPool();
    InitCommandBuffer();
}

void Quack::GPUCommandBufferVulkan::Create() {
    CreateCommandPool();
    CreateCommandBuffer();
}

Quack::GPUCommandBufferVulkan::~GPUCommandBufferVulkan() {
    // const auto& context = dynamic_cast<GPUContextVulkan*>(Application::GetInstance().GetContext());
    // vkDestroyCommandPool(context->GetDevice(), _commandPool, nullptr);
}

void Quack::GPUCommandBufferVulkan::InitCommandPool() {
    _commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    _commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    const auto& context = dynamic_cast<GPUContextVulkan*>(_desc.Context);
    _commandPoolCreateInfo.queueFamilyIndex = context->GetQueueFamilyIndices().graphicsFamily.value();
}

void Quack::GPUCommandBufferVulkan::CreateCommandPool() {
    const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
    if (vkCreateCommandPool(device->GetDevice(), &_commandPoolCreateInfo, nullptr, &_commandPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create command pool!");
    }
}

void Quack::GPUCommandBufferVulkan::InitCommandBuffer() {
    _commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    _commandBufferAllocateInfo.commandPool = _commandPool;
    _commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    _commandBufferAllocateInfo.commandBufferCount = 1;
}

void Quack::GPUCommandBufferVulkan::CreateCommandBuffer() {
    const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
    if (vkAllocateCommandBuffers(device->GetDevice(), nullptr, &_commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create command buffer!");
    }
}

const VkCommandPool& Quack::GPUCommandBufferVulkan::GetCommandPool() const {
    return _commandPool;
}

const VkCommandBuffer& Quack::GPUCommandBufferVulkan::GetCommandBuffer() const {
    return _commandBuffer;
}

void Quack::GPUCommandBufferVulkan::Begin() {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(_commandBuffer, &info) != VK_SUCCESS) {
        throw std::runtime_error("Failed to begin recording command buffer!");
    }
}

void Quack::GPUCommandBufferVulkan::End() {
    if (vkEndCommandBuffer(_commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to record command buffer!");
    }
}