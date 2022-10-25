#include "quack/quack.h"
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan_core.h>

Quack::GPUAdapterVulkan::GPUAdapterVulkan(const GPUAdapterDescription& desc) 
    : Quack::GPUAdapter(desc)
    , _adapter(nullptr)
{
    const auto& context = dynamic_cast<GPUContextVulkan*>(GetContext());
    PickSuitableAdapter(context->GetInstance(), context->GetSurface());;
}

Quack::GPUAdapterVulkan::~GPUAdapterVulkan() {}

void Quack::GPUAdapterVulkan::PickSuitableAdapter(const VkInstance& instance, const VkSurfaceKHR& surface) {
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);
    if (count == 0) {

        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> adapters(count);
    vkEnumeratePhysicalDevices(instance, &count, adapters.data());

    for (const auto& adapter : adapters) {
        if (IsAdapterSuitable(adapter, surface)) {
            _adapter = adapter;
            break;
        }
    }

    if (_adapter == VK_NULL_HANDLE) {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }
}

bool Quack::GPUAdapterVulkan::IsAdapterSuitable(const VkPhysicalDevice& adapter, const VkSurfaceKHR& surface) const {
    QueueFamilyIndices indices = FindQueueFamiliesIndices(adapter, surface);
    bool isExtensionsSupported = IsAdapterExtensionsSupported(adapter);

    bool isSwapChainAdequate = false;
    if (isExtensionsSupported) {
        SwapChainSupportDetails swapChainSupport = FindQuerySwapChainSupport(adapter, surface);
        isSwapChainAdequate = !swapChainSupport.SurfaceForamts.empty() && !swapChainSupport.PresentModes.empty(); 
    }

    return indices.IsComplete() && isExtensionsSupported && isSwapChainAdequate;
}

Quack::QueueFamilyIndices Quack::GPUAdapterVulkan::FindQueueFamiliesIndices(const VkPhysicalDevice& adapter, 
    const VkSurfaceKHR& surface)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(adapter, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(adapter, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.GraphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(adapter, i, surface, &presentSupport);

        if (presentSupport) {
            indices.PresentFamily = i;
        }

        if (indices.IsComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool Quack::GPUAdapterVulkan::IsAdapterExtensionsSupported(const VkPhysicalDevice& adapter) const {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(adapter, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(adapter, nullptr, &extensionCount, availableExtensions.data());

    const auto& extensions = dynamic_cast<GPUContextVulkan*>(GetContext())->GetExtensions();
    std::set<std::string> requiredExtensions(extensions.begin(), extensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

Quack::SwapChainSupportDetails Quack::GPUAdapterVulkan::FindQuerySwapChainSupport(const VkPhysicalDevice& adapter,
    const VkSurfaceKHR& surface)
{
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(adapter, surface, &details.SurfaceCapabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(adapter, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.SurfaceForamts.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(adapter, surface, &formatCount, details.SurfaceForamts.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(adapter, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.PresentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(adapter, surface, &presentModeCount, details.PresentModes.data());
    }

    return details;
}

const VkFormat& Quack::GPUAdapterVulkan::FindSupportedFormat(const std::vector<VkFormat>& candidates, 
    VkImageTiling tiling, VkFormatFeatureFlags features) const
{
    for (const auto& format : candidates) {
        VkFormatProperties formatProps;
        vkGetPhysicalDeviceFormatProperties(_adapter, format, &formatProps);

        if (tiling == VK_IMAGE_TILING_LINEAR && (formatProps.linearTilingFeatures & features) == features) {
            return format;
        }
        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (formatProps.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error("Failed to find supported format!");
}

const VkPhysicalDevice& Quack::GPUAdapterVulkan::GetAdapter() const {
    return _adapter;
}