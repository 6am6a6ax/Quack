#ifndef QUACK_GPU_ADAPTER_VULKAN_H
#define QUACK_GPU_ADAPTER_VULKAN_H

#include <vector>
#include <cstdint>
#include <optional>

#include <vulkan/vulkan_core.h>

#include "quack/graphics/gpu_adapter.h"

namespace Quack {

struct QueueFamilyIndices {
    std::optional<uint32_t> GraphicsFamily;
    std::optional<uint32_t> PresentFamily;

    bool IsComplete() {
        return GraphicsFamily.has_value() && PresentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR SurfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> SurfaceForamts;
    std::vector<VkPresentModeKHR> PresentModes;
};

class GPUAdapterVulkan final : public GPUAdapter {
public:
    explicit GPUAdapterVulkan(const GPUAdapterDescription&);
    ~GPUAdapterVulkan() override = default;

public:
    static QueueFamilyIndices FindQueueFamiliesIndices(VkPhysicalDevice adapter, VkSurfaceKHR surface);
    static SwapChainSupportDetails FindQuerySwapChainSupport(VkPhysicalDevice adapter, VkSurfaceKHR surface);

public:
    const VkFormat& FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, 
        VkFormatFeatureFlags features) const;

public:
    VkPhysicalDevice GetAdapterHandle() const;

private:
    void PickSuitableAdapter(VkInstance instance, VkSurfaceKHR surface);

    bool IsAdapterSuitable(VkPhysicalDevice adapter, VkSurfaceKHR surface) const;
    bool IsAdapterExtensionsSupported(VkPhysicalDevice adapter) const;

private:
    VkPhysicalDevice _adapter;
};
}

#endif