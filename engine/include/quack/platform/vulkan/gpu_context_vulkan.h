#ifndef QUACK_GPU_CONTEXT_VULKAN_H
#define QUACK_GPU_CONTEXT_VULKAN_H

#include <cstdint>
#include <optional>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "quack/core/window.h"
#include "quack/graphics/gpu_context.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


namespace Quack {
class GPUContextVulkan final : public GPUContext {
public:
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
public:
    GPUContextVulkan(const GPUContext::Description& desc);

    void Init() override;
    void SwapBuffers() override {}

public:
    const VkInstance& GetInstance() const { return instance; }
    const VkSurfaceKHR& GetSurface() const { return surface; }
    const std::vector<const char*>& GetExtensions() const { return deviceExtensions; }
    const std::vector<const char*>& GetValidationLayers() const { return validationLayers; }

    bool IsValidationLayersEnabled() const { return enableValidationLayers; }
    
private:
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

public:
    VkSurfaceKHR GetSurface()  { return surface; }

private:
    void CreateInstance();
    void SetupDebugMessenger();
    void CreateSurface();

private:
    VkInstance instance;
    VkSurfaceKHR surface;

    VkDebugUtilsMessengerEXT debugMessenger;

    const bool enableValidationLayers = true;

    bool CheckValidationLayerSupport();
    std::vector<const char*> GetRequiredExtensions();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
};
}


#endif