#include "quack/platform/vulkan/gpu_device_vulkan.h"
#include "quack/quack.h"
#include <stdexcept>
#include <vulkan/vulkan_core.h>

Quack::GPUPipelineVulkan::GPUPipelineVulkan(const Quack::GPUPipelineDescription& desc)
    : Quack::GPUPipeline(desc)
    , _vertexShaderStageInfo({})
    , _fragmentShaderStageInfo({})
    , _dynamicStateInfo({})
    , _vertexInputInfo({})
    , _inputAssemblyInfo({})
    , _viewport({})
    , _viewportStateInfo({})
    , _scissor({})
    , _rasterizerStateInfo({})
    , _multisamplingStateInfo({})
    , _colorBlendAttachmentState({})
    , _colorBlendStateInfo({})
    , _pipelineLayout(VK_NULL_HANDLE)
    , _pipelineLayoutInfo({})
    , _pipeline(VK_NULL_HANDLE)
    , _pipelineInfo({})
{
    Init();
    Create();
}

Quack::GPUPipelineVulkan::~GPUPipelineVulkan() {
    const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
    vkDestroyPipeline(device->GetDevice(), _pipeline, nullptr);
    vkDestroyPipelineLayout(device->GetDevice(), _pipelineLayout, nullptr);
}

void Quack::GPUPipelineVulkan::Init() {
    InitVertexShader();
    InitFragmentShader();
    
    InitVertexInput();
    InitInputAssembly();

    InitViewport();
    InitScissor();

    InitRasterizer();
    InitMultisampling();
    InitColorBlending();

    InitDynamicState();

    InitPipelineLayout();
}

void Quack::GPUPipelineVulkan::Create() {
    CreatePipelineLayout();

    InitPipeline();
    CreatePipeline();
}

void Quack::GPUPipelineVulkan::InitVertexShader() {
    _vertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _vertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    _vertexShaderStageInfo.module = dynamic_cast<GPUShaderProgramVulkan*>(_desc.Vertex)->GetModule();
    _vertexShaderStageInfo.pName = "main";

    _shaderStages.push_back(_vertexShaderStageInfo);
}

void Quack::GPUPipelineVulkan::InitFragmentShader() {
    _fragmentShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _fragmentShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    _fragmentShaderStageInfo.module = dynamic_cast<GPUShaderProgramVulkan*>(_desc.Fragment)->GetModule();
    _fragmentShaderStageInfo.pName = "main";

    _shaderStages.push_back(_fragmentShaderStageInfo);
}

void Quack::GPUPipelineVulkan::InitDynamicState() {
    _dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    _dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(_dynamicStates.size());
    _dynamicStateInfo.pDynamicStates = _dynamicStates.data();
}

void Quack::GPUPipelineVulkan::InitVertexInput() {
    _vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    _vertexInputInfo.vertexBindingDescriptionCount = 0;
    _vertexInputInfo.pVertexBindingDescriptions = nullptr;
    _vertexInputInfo.vertexAttributeDescriptionCount = 0;
    _vertexInputInfo.pVertexAttributeDescriptions = nullptr;
}

void Quack::GPUPipelineVulkan::InitInputAssembly() {
    _inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    _inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    _inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;
}

void Quack::GPUPipelineVulkan::InitViewport() {
    _viewport.x = 0.0f;
    _viewport.y = 0.0f;

    const auto& context = dynamic_cast<GPUContextVulkan*>(_desc.Context);
    const auto& swapChain = dynamic_cast<GPUSwapChainVulkan*>(_desc.SwapChain);
    _viewport.width = static_cast<float>(swapChain->getSwapChainExtent().width);
    _viewport.height = static_cast<float>(swapChain->getSwapChainExtent().height);

    _viewport.minDepth = 0.0f;
    _viewport.maxDepth = 1.0f;

    _viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    _viewportStateInfo.viewportCount = 1;
    _viewportStateInfo.pViewports = &_viewport;
    _viewportStateInfo.scissorCount = 1;
    _viewportStateInfo.pScissors = &_scissor;
}

void Quack::GPUPipelineVulkan::InitScissor() {
    _scissor.offset = {0, 0};
    const auto& swapChain = dynamic_cast<GPUSwapChainVulkan*>(_desc.SwapChain);
    _scissor.extent = swapChain->getSwapChainExtent();
}

void Quack::GPUPipelineVulkan::InitRasterizer() {
    _rasterizerStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    _rasterizerStateInfo.depthClampEnable = VK_FALSE;
    _rasterizerStateInfo.rasterizerDiscardEnable = VK_FALSE;
    _rasterizerStateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    _rasterizerStateInfo.lineWidth = 1.0f;
    _rasterizerStateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    _rasterizerStateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    _rasterizerStateInfo.depthBiasClamp = VK_FALSE;
    _rasterizerStateInfo.depthBiasConstantFactor = 0.0f;
    _rasterizerStateInfo.depthBiasClamp = 0.0f;
    _rasterizerStateInfo.depthBiasSlopeFactor = 0.0f;
}

void Quack::GPUPipelineVulkan::InitMultisampling() {
    _multisamplingStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    _multisamplingStateInfo.sampleShadingEnable = VK_FALSE;
    _multisamplingStateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    _multisamplingStateInfo.minSampleShading = 1.0f;
    _multisamplingStateInfo.pSampleMask = nullptr;
    _multisamplingStateInfo.alphaToCoverageEnable = VK_FALSE;
    _multisamplingStateInfo.alphaToOneEnable = VK_FALSE;
}

void Quack::GPUPipelineVulkan::InitColorBlending() {
    _colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    _colorBlendAttachmentState.blendEnable = VK_FALSE;

    _colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    _colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    _colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;

    _colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    _colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    _colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

    _colorBlendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    _colorBlendStateInfo.logicOpEnable = VK_FALSE;
    _colorBlendStateInfo.logicOp = VK_LOGIC_OP_COPY;
    _colorBlendStateInfo.attachmentCount = 1;
    _colorBlendStateInfo.pAttachments = &_colorBlendAttachmentState;
    _colorBlendStateInfo.blendConstants[0] = 0.0f;
    _colorBlendStateInfo.blendConstants[1] = 0.0f;
    _colorBlendStateInfo.blendConstants[2] = 0.0f;
    _colorBlendStateInfo.blendConstants[3] = 0.0f;
}

void Quack::GPUPipelineVulkan::InitPipelineLayout() {
    _pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    _pipelineLayoutInfo.setLayoutCount = 0;
    _pipelineLayoutInfo.pSetLayouts = nullptr;
    _pipelineLayoutInfo.pushConstantRangeCount = 0;
    _pipelineLayoutInfo.pPushConstantRanges = nullptr;
}

void Quack::GPUPipelineVulkan::CreatePipelineLayout() {
    const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
    if (vkCreatePipelineLayout(device->GetDevice(), &_pipelineLayoutInfo, nullptr, &_pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void Quack::GPUPipelineVulkan::InitPipeline() {
    _pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    _pipelineInfo.stageCount = 2;
    _pipelineInfo.pStages = _shaderStages.data();
    _pipelineInfo.pVertexInputState = &_vertexInputInfo;
    _pipelineInfo.pInputAssemblyState = &_inputAssemblyInfo;
    _pipelineInfo.pViewportState = &_viewportStateInfo;
    _pipelineInfo.pRasterizationState = &_rasterizerStateInfo;
    _pipelineInfo.pMultisampleState = &_multisamplingStateInfo;
    _pipelineInfo.pColorBlendState = &_colorBlendStateInfo;
    _pipelineInfo.pDynamicState = &_dynamicStateInfo;
    _pipelineInfo.layout = _pipelineLayout;
    _pipelineInfo.renderPass = dynamic_cast<GPUSwapChainVulkan*>(_desc.SwapChain)->GetRenderPass();
    _pipelineInfo.subpass = 0;
    _pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
}

void Quack::GPUPipelineVulkan::CreatePipeline() {
    const auto& device = dynamic_cast<GPUDeviceVulkan*>(_desc.Device);
    if(vkCreateGraphicsPipelines(device->GetDevice(), VK_NULL_HANDLE, 1, &_pipelineInfo, nullptr, &_pipeline) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create graphics pipeline!");      
    }
}

void Quack::GPUPipelineVulkan::BindVk() {
    vkCmdBindPipeline(
        dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer)->GetCommandBuffer(), 
        VK_PIPELINE_BIND_POINT_GRAPHICS, 
        _pipeline
    );

    SetViewport();
    SetScissor();
}

void Quack::GPUPipelineVulkan::SetViewport() {
    vkCmdSetViewport(
        dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer)->GetCommandBuffer(),
        0,
        1,
        &_viewport    
    );
}

void Quack::GPUPipelineVulkan::SetScissor() {
    vkCmdSetScissor(
        dynamic_cast<GPUCommandBufferVulkan*>(_desc.CommandBuffer)->GetCommandBuffer(),
        0,
        1,
        &_scissor
    );
}