#ifndef QUACK_GPU_DEVICE_VULKAN_H
#define QUACK_GPU_DEVICE_VULKAN_H

#include "quack/graphics/gpu_device.h"

namespace Quack {
class GPUDeviceVulkan final : public GPUDevice {
public:
    GPUDeviceVulkan();
    ~GPUDeviceVulkan() override;
};
}

#endif