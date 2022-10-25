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
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

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
    VkExtent2D GetExtent2D() const { return swapChainExtent; }
    std::vector<VkImageView> GetSwapChainImageViews() const { return swapChainImageViews; }
    VkSurfaceKHR GetSurface()  { return surface; }
    QueueFamilyIndices GetQueueFamilyIndices() { return FindQueueFamilies(physicalDevice); }
    VkSwapchainKHR GetSwapChain() const { return swapChain; }
    VkQueue GetGraphicsQueue() const { return graphicsQueue; }
    VkQueue GetPresentQueue() const { return presentQueue; }

private:
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;

    const bool enableValidationLayers = true;

    void CreateInstance();
    void SetupDebugMessenger();
    void CreateSurface();
    void CreateSwapChain();
    void CreateImageViews();

    bool CheckValidationLayerSupport();
    std::vector<const char*> GetRequiredExtensions();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    bool IsDeviceSuitable(VkPhysicalDevice);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> & avaliablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};
}


#endif