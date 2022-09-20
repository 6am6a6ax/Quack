#ifndef QUACK_GPU_DEVICE_OPENGL_H
#define QUACK_GPU_DEVICE_OPENGL_H

#include "quack/graphics/gpu_device.h"

#include "quack/graphics/gpu_shader.h"
#include "quack/graphics/gpu_shader_program.h"
#include "quack/graphics/gpu_vertex_array.h"

namespace Quack {
class GPUDeviceOpenGL final : public GPUDevice {
public:
    GPUBuffer * CreateBuffer(const GPUBuffer::Description &) const override;
    GPUShader * CreateShader(const GPUShaderDescription &) const override;
    GPUShaderProgram * CreateShaderProgram(const GPUShaderProgramDescription &) const override;
    GPUVertexArray * CreateVertexArray() const override;
};
}

#endif
