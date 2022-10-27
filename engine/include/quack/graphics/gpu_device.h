#ifndef QUACK_GPU_DEVICE_H
#define QUACK_GPU_DEVICE_H

#include "gpu_context.h"
#include "gpu_adapter.h"
#include "gpu_buffer.h"
#include "gpu_shader.h"
#include "gpu_vertex_array.h"
#include "gpu_shader_program.h"
#include "gpu_texture.h"
#include "gpu_framebuffer.h"
#include "quack/graphics/gpu_swap_chain.h"
#include "quack/math/math.h"
#include <bitset>
#include <cstdint>
#include <memory>

namespace Quack {
class GPUShader;
class GPUShaderDescription;

class GPUShaderProgram;
class GPUShaderProgramDescription;

struct GPUDeviceDescription {
    std::shared_ptr<GPUContext> Context;
    std::shared_ptr<GPUAdapter> Adapter;
};

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
    GPUDevice(const GPUDeviceDescription& desc);
    virtual ~GPUDevice() = default;

public:
    virtual void Enable(CommonFlag) const {};
    virtual void Disable(CommonFlag) const {};

public:
    virtual void SetDepthFunc(DepthFuncFlag) const {}; 

public:
    virtual void Clear(ClearFlag) const {}; 
    virtual void ClearColor(const Vector4f& color) const {};

public:
    virtual std::shared_ptr<GPUBuffer> CreateBuffer(const GPUBuffer::Description &) const {};

    virtual std::shared_ptr<GPUTexture> CreateTexture(const GPUTextureDescription &) const {};
    virtual std::shared_ptr<GPUFramebuffer> CreateFramebuffer(const GPUFramebufferDescription &) const {};
    virtual std::shared_ptr<GPUSwapChain> CreateSwapChain(const GPUSwapChainDescription &) const {};

    virtual std::shared_ptr<GPUShader> CreateShader(const GPUShaderDescription &) const {};
    virtual std::shared_ptr<GPUShaderProgram> CreateShaderProgram(const GPUShaderProgramDescription &) const {};
    
    virtual std::shared_ptr<GPUVertexArray> CreateVertexArray() const {};

public:
    virtual void DrawIndexed(uint32_t count) const {};

public:
    // virtual const GPUAdapter * GetAdapter() const = 0;

public:
    const std::shared_ptr<GPUAdapter>& GetAdapter() const;
    const std::shared_ptr<GPUContext>& GetContext() const;

private:
    GPUDeviceDescription _desc;
};
}

#endif