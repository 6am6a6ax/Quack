#ifndef QUACK_GPU_CONTEXT_VULKAN_H
#define QUACK_GPU_CONTEXT_VULKAN_H

#include <vector>
#include <vulkan/vulkan_core.h>
#include "quack/graphics/gpu_context.h"

namespace Quack {
class GPUContextVulkan final : public GPUContext {
public:
    explicit GPUContextVulkan(const Description&);
    ~GPUContextVulkan() override;

public:
    VkInstance GetInstanceHandle() const;
    VkSurfaceKHR GetSurfaceHandle() const;    
    const std::vector<const char*>& GetExtensions() const;

    bool IsValidationLayersEnabled() const;
    const std::vector<const char*>& GetValidationLayers() const;

private:
    void CreateInstance();
    void CreateSurface();

    void SetupDebugMessenger();

private:
    bool IsValidationLayersSupported() const;
    std::vector<const char*> GetRequiredExtensions() const;

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

private:
    const std::vector<const char*> _extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    const std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

private:
    VkInstance _instance;
    VkSurfaceKHR _surface;

    bool _isValidationLayersEnabled;
    VkDebugUtilsMessengerEXT _debugMessenger;
};
}

#endif