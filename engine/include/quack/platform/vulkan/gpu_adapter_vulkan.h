#ifndef QUACK_GPU_ADAPTER_VULKAN_H
#define QUACK_GPU_ADAPTER_VULKAN_H

#include <vector>
#include <cstdint>

#include <vulkan/vulkan_core.h>

#include "quack/graphics/gpu_adapter.h"
#include "quack/graphics/gpu_context.h"

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
    GPUAdapterVulkan(const GPUAdapterDescription&);
    ~GPUAdapterVulkan();

public:
    static QueueFamilyIndices FindQueueFamiliesIndices(const VkPhysicalDevice& adapter, const VkSurfaceKHR& surface);
    static SwapChainSupportDetails FindQuerySwapChainSupport(const VkPhysicalDevice& adapter, 
        const VkSurfaceKHR& surface);

public:
    const VkFormat& FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, 
        VkFormatFeatureFlags features) const;

public:
    const VkPhysicalDevice& GetAdapter() const;

private:
    void PickSuitableAdapter(const VkInstance& instance, const VkSurfaceKHR& surface);

    bool IsAdapterSuitable(const VkPhysicalDevice& adapter, const VkSurfaceKHR& surface) const;
    bool IsAdapterExtensionsSupported(const VkPhysicalDevice& adapter) const;

private:
    VkPhysicalDevice _adapter;
};
}

#endif