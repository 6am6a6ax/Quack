#ifndef QUACK_GPU_PIPELINE_H
#define QUACK_GPU_PIPELINE_H

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_shader.h"
#include "quack/graphics/gpu_resource.h"

namespace Quack {
struct GPUPipelineDescription {
    GPUShader * Shader;
    GPUBuffer::Layout Layout;
};

class GPUPipeline : public GPUResource {
public:
    ~GPUPipeline() override {}

public:
    void Bind() const override {}
    void Unbind() const override {}

public:
    const GPUPipelineDescription & GetDescription() { return _desc; }
    void SetDescription(const GPUPipelineDescription & desc) { _desc = desc; }

private:
    GPUPipelineDescription _desc;
};
}

#endif