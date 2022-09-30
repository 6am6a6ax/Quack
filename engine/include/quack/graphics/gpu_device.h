#ifndef QUACK_GPU_DEVICE_H
#define QUACK_GPU_DEVICE_H

#include "gpu_buffer.h"
#include "gpu_shader.h"
#include "gpu_vertex_array.h"
#include "gpu_shader_program.h"
#include "gpu_texture.h"
#include "gpu_framebuffer.h"

namespace Quack {
class GPUDevice {
public:
    virtual ~GPUDevice() = default;

public:
    virtual GPUShader * CreateShader(const GPUShaderDescription &) const = 0;
    virtual GPUBuffer * CreateBuffer(const GPUBuffer::Description &) const = 0;
    virtual GPUShaderProgram * CreateShaderProgram(const GPUShaderProgramDescription &) const = 0;
    virtual GPUVertexArray * CreateVertexArray() const = 0;
    virtual GPUTexture * CreateTexture(const GPUTextureDescription &) const = 0;
    virtual GPUFramebuffer * CreateFramebuffer(const GPUFramebufferDescription &) const = 0;

public:
//    virtual const GPUAdapter * GetAdapter() const = 0;
};
}

#endif