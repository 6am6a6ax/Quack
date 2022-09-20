#ifndef QUACK_GPU_DEVICE_OPENGL_H
#define QUACK_GPU_DEVICE_OPENGL_H

#include "quack/graphics/gpu_device.h"

namespace Quack {
class GPUDeviceOpenGL final : public GPUDevice {
public:
    GPUBuffer * CreateBuffer(const GPUBuffer::Description &) const override;
    GPUShader * CreateShader(const GPUShaderDescription &) const override;
    GPUShaderProgram * CreateShaderProgram(const GPUShaderProgramDescription &) const override;
    GPUVertexArray * CreateVertexArray() const override;
    GPUTexture * CreateTexture(const GPUTextureDescription &) const override;
};
}

#endif
