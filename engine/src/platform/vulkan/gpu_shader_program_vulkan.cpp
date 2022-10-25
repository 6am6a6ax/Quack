#include "quack/quack.h"
#include <cstddef>
#include <cstdint>
#include <vulkan/vulkan_core.h>

Quack::GPUShaderProgramVulkan::GPUShaderProgramVulkan(const GPUShaderProgramDescription& desc)
    : GPUShaderProgram(desc)
    , _module(VK_NULL_HANDLE)
    , _info({})
    , _src({})
{
    Init();
    Create();
}

Quack::GPUShaderProgramVulkan::~GPUShaderProgramVulkan() {
    const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
    vkDestroyShaderModule(device->GetDevice(), _module, nullptr);
}

void Quack::GPUShaderProgramVulkan::Init() {
    _src = Read(GetDescription().Name); // TODO

    _info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    _info.codeSize = _src.size();
    _info.pCode = reinterpret_cast<const uint32_t*>(_src.data());
}

void Quack::GPUShaderProgramVulkan::Create() {
    const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
    if (vkCreateShaderModule(device->GetDevice(), &_info, nullptr, &_module) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module!");
    }

    auto bp =  1;
}

std::vector<char> Quack::GPUShaderProgramVulkan::Read(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}