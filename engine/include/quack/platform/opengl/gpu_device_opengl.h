#ifndef QUACK_GPU_DEVICE_OPENGL_H
#define QUACK_GPU_DEVICE_OPENGL_H

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_framebuffer.h"
#include "quack/graphics/gpu_texture.h"
#include "quack/graphics/gpu_vertex_array.h"
#include "quack/math/math.h"
#include <cstdint>
#include <memory>

namespace Quack {
class GPUDeviceOpenGL final : public GPUDevice {
public:
    ~GPUDeviceOpenGL() override = default;

public:
    void Enable(CommonFlag) const override;
    void Disable(CommonFlag) const override;

public:
    void SetDepthFunc(DepthFuncFlag) const override;

public:
    void Clear(ClearFlag) const override;
    void ClearColor(const Vector4f& color) const override;

public:
    std::shared_ptr<GPUBuffer> CreateBuffer(const GPUBuffer::Description&) const override;
    std::shared_ptr<GPUShader> CreateShader(const GPUShaderDescription&) const override;
    std::shared_ptr<GPUShaderProgram> CreateShaderProgram(const GPUShaderProgramDescription&) const override;
    std::shared_ptr<GPUVertexArray> CreateVertexArray() const override;
    std::shared_ptr<GPUTexture> CreateTexture(const GPUTextureDescription&) const override;
    std::shared_ptr<GPUFramebuffer> CreateFramebuffer(const GPUFramebufferDescription&) const override;

public:
    void DrawIndexed(uint32_t count) const override;
};
}

#endif
