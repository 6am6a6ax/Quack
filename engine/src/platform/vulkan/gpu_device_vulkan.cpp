#include "quack/quack.h"

Quack::GPUDeviceVulkan::GPUDeviceVulkan(const GPUDeviceDescription& desc) 
    : Quack::GPUDevice(desc) 
    , _device(VK_NULL_HANDLE)
    , _graphicsQueue(VK_NULL_HANDLE)
    , _presentQueue(VK_NULL_HANDLE)
{
    const auto& adapter = std::dynamic_pointer_cast<GPUAdapterVulkan>(GetAdapter());
    const auto& context = std::dynamic_pointer_cast<GPUContextVulkan>(GetContext());

    QueueFamilyIndices indices = GPUAdapterVulkan::FindQueueFamiliesIndices(adapter->GetAdapterHandle(), context->GetSurfaceHandle());

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.GraphicsFamily.value(), indices.PresentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(context->GetExtensions().size());
    createInfo.ppEnabledExtensionNames = context->GetExtensions().data();

    if (context->IsValidationLayersEnabled()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(context->GetValidationLayers().size());
        createInfo.ppEnabledLayerNames = context->GetValidationLayers().data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(adapter->GetAdapterHandle(), &createInfo, nullptr, &_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(_device, indices.GraphicsFamily.value(), 0, &_graphicsQueue);
    vkGetDeviceQueue(_device, indices.PresentFamily.value(), 0, &_presentQueue);
}

Quack::GPUDeviceVulkan::~GPUDeviceVulkan() {
    vkDestroyDevice(_device, nullptr);
}

// std::shared_ptr<Quack::GPUFramebuffer> Quack::GPUDeviceVulkan::CreateFramebuffer(
//     const GPUFramebufferDescription& desc) const 
// {
//     // return std::make_shared<GPUFramebufferVulkan>(desc);
// }

std::shared_ptr<Quack::GPUSwapChain> Quack::GPUDeviceVulkan::CreateSwapChain(
    const GPUSwapChainDescription& desc) const 
{
    return std::make_shared<GPUSwapChainVulkan>(desc);
}

std::shared_ptr<Quack::GPUShaderProgram> Quack::GPUDeviceVulkan::CreateShaderProgram(
    const GPUShaderProgramDescription& desc) const 
{
    return std::make_shared<GPUShaderProgramVulkan>(desc);
}

VkDevice Quack::GPUDeviceVulkan::GetDeviceHandle() const {
    return _device;
}

VkQueue Quack::GPUDeviceVulkan::GetGraphicsQueue() const {
    return _graphicsQueue;
}

VkQueue Quack::GPUDeviceVulkan::GetPresentQueue() const {
    return _presentQueue;
}

