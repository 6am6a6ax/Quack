#include "quack/core/application.h"
#include "quack/graphics/gpu_shader.h"
#include "quack/platform/opengl/gpu_shader_opengl.h"
#include "quack/quack.h"
#include <cstddef>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan_core.h>

Quack::GPUShaderProgramVulkan::GPUShaderProgramVulkan(const GPUShaderProgramDescription& desc)
    : GPUShaderProgram(desc), _module(nullptr), _info({})
{
    Init();
    Create();
}

Quack::GPUShaderProgramVulkan::~GPUShaderProgramVulkan() {
    GPUContextVulkan* context = dynamic_cast<GPUContextVulkan*>(Application::GetInstance().GetContext());
    vkDestroyShaderModule(context->GetDevice(), _module, nullptr);
}

void Quack::GPUShaderProgramVulkan::Init() {
    std::vector<char> src = Read(GetDescription().Name); // TODO

    _info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    _info.codeSize = src.size();
    _info.pCode = reinterpret_cast<const uint32_t*>(src.data());
}

void Quack::GPUShaderProgramVulkan::Create() {
    GPUContextVulkan* context = dynamic_cast<GPUContextVulkan*>(Application::GetInstance().GetContext());
    if (vkCreateShaderModule(context->GetDevice(), &_info, nullptr, &_module) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module!");
    }
}

std::vector<char> Quack::GPUShaderProgramVulkan::Read(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file!");
    }

    size_t size = static_cast<size_t>(file.tellg());
    std::vector<char> result(size);

    file.seekg(0);
    file.read(result.data(), size);
    file.close();

    return result;
}