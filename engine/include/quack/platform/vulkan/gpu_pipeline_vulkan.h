#ifndef QUACK_GPU_PIPELINE_VULKAN_H
#define QUACK_GPU_PIPELINE_VULKAN_H

#include <vector>
#include <vulkan/vulkan_core.h>
#include "quack/graphics/gpu_pipeline.h"

namespace Quack {
class GPUPipelineVulkan final : public GPUPipeline {
public:
    explicit GPUPipelineVulkan(const GPUPipelineDescription&);
    ~GPUPipelineVulkan() override;

public:
    void Bind() const override;
    void Unbind() const override {}

    void BindVk();

private:
    void Init();
    void Create();

private:
    void InitVertexShader();
    void InitFragmentShader();

    void InitDynamicState();

    void InitVertexInput();
    void InitInputAssembly();

    void InitViewport();
    void InitScissor();

    void InitRasterizer();
    void InitMultisampling();
    void InitColorBlending();

    void InitPipelineLayout();
    void InitPipeline();

private:
    void CreatePipelineLayout();
    void CreatePipeline();

    void SetViewport();
    void SetScissor();

private:
    VkPipelineShaderStageCreateInfo _vertexShaderStageInfo;
    VkPipelineShaderStageCreateInfo _fragmentShaderStageInfo;

    std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;

    std::vector<VkDynamicState> _dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };
    VkPipelineDynamicStateCreateInfo _dynamicStateInfo;

    VkPipelineVertexInputStateCreateInfo _vertexInputInfo;
    VkPipelineInputAssemblyStateCreateInfo _inputAssemblyInfo;

    VkViewport _viewport;
    VkPipelineViewportStateCreateInfo _viewportStateInfo;
    VkRect2D _scissor;

    VkPipelineRasterizationStateCreateInfo _rasterizerStateInfo;
    VkPipelineMultisampleStateCreateInfo _multisamplingStateInfo;

    VkPipelineColorBlendAttachmentState _colorBlendAttachmentState;
    VkPipelineColorBlendStateCreateInfo _colorBlendStateInfo;

    // Shaders uniforms...
    VkPipelineLayout _pipelineLayout;
    VkPipelineLayoutCreateInfo _pipelineLayoutInfo;

    VkPipeline _pipeline;
    VkGraphicsPipelineCreateInfo _pipelineInfo;
};
}

#endif