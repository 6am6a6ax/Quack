#ifndef QUACK_GPU_SHADER_PROGRAM_VULKAN_H
#define QUACK_GPU_SHADER_PROGRAM_VULKAN_H

#include "quack/graphics/gpu_shader_program.h"
#include "quack/graphics/gpu_shader_program_description.h"
#include <vulkan/vulkan_core.h>

namespace Quack {
class GPUShaderProgramVulkan final : public GPUShaderProgram {
public:
    explicit GPUShaderProgramVulkan(const GPUShaderProgramDescription&);
    ~GPUShaderProgramVulkan() override;

public:
    void Bind() const override {}
    void Unbind() const override {}

public:
    VkShaderModule GetModuleHandle() const { return _module; }

private:
    void Init();
    void Create();

private:
    static std::vector<char> Read(const std::string& filename);

private:
    VkShaderModule _module;
    VkShaderModuleCreateInfo _info;
    std::vector<char> _src;
};
}

#endif