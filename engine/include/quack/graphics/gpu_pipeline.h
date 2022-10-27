#ifndef QUACK_GPU_PIPELINE_H
#define QUACK_GPU_PIPELINE_H

#include "quack/graphics/gpu_command_buffer.h"
#include "quack/graphics/gpu_context.h"
#include "quack/graphics/gpu_shader.h"
#include "quack/graphics/gpu_resource.h"
#include "quack/graphics/gpu_render_pass.h"

namespace Quack {
class GPUContext;
class GPUDevice;

struct GPUPipelineDescription {
    std::shared_ptr<GPUShaderProgram> Vertex;
    std::shared_ptr<GPUShaderProgram> Fragment;

    GPURenderPass* RenderPass;
    GPUCommandBuffer* CommandBuffer;

    GPUContext* Context;
    GPUDevice* Device;

    GPUSwapChain* SwapChain;

    GPUBuffer::Layout Layout;
};

class GPUPipeline : public GPUResource {
public:
    GPUPipeline(const GPUPipelineDescription& desc) : _desc(desc) {}
    ~GPUPipeline() override {}

public:
    void Bind() const override {}
    void Unbind() const override {}

public:
    GPUCommandBuffer* GetCommandBuffer() const { return _desc.CommandBuffer; }

    const GPUPipelineDescription & GetDescription() { return _desc; }
    void SetDescription(const GPUPipelineDescription & desc) { _desc = desc; }

protected:
    GPUPipelineDescription _desc;
};
}

#endif