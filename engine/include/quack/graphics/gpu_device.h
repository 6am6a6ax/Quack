#ifndef QUACK_GPU_DEVICE_H
#define QUACK_GPU_DEVICE_H

#include "gpu_buffer.h"
#include "gpu_shader.h"
#include "gpu_vertex_array.h"
#include "gpu_shader_program.h"
#include "gpu_texture.h"
#include "gpu_framebuffer.h"
#include "quack/math/math.h"
#include <bitset>
#include <cstdint>
#include <memory>

namespace Quack {
class GPUDevice {
public:
    enum class CommonFlag : uint8_t {
        DEPTH_TEST
    };

    enum class ClearFlag : uint8_t {
        COLOR_BUFFER, DEPTH_BUFFER
    };

    enum class DepthFuncFlag : uint8_t {
        LESS
    };

public:
    virtual ~GPUDevice() = default;

public:
    virtual void Enable(CommonFlag) const = 0;
    virtual void Disable(CommonFlag) const = 0;

public:
    virtual void SetDepthFunc(DepthFuncFlag) const = 0; 

public:
    virtual void Clear(ClearFlag) const = 0; 
    virtual void ClearColor(const Vector4f& color) const = 0;

public:
    virtual std::shared_ptr<GPUBuffer> CreateBuffer(const GPUBuffer::Description &) const = 0;

    virtual std::shared_ptr<GPUTexture> CreateTexture(const GPUTextureDescription &) const = 0;
    virtual std::shared_ptr<GPUFramebuffer> CreateFramebuffer(const GPUFramebufferDescription &) const = 0;

    virtual std::shared_ptr<GPUShader> CreateShader(const GPUShaderDescription &) const = 0;
    virtual std::shared_ptr<GPUShaderProgram> CreateShaderProgram(const GPUShaderProgramDescription &) const = 0;
    
    virtual std::shared_ptr<GPUVertexArray> CreateVertexArray() const = 0;

public:
    virtual void DrawIndexed(uint32_t count) const = 0;

public:
    // virtual const GPUAdapter * GetAdapter() const = 0;
};
}

#endif