#ifndef QUACK_GPU_SWAP_CHAIN_H
#define QUACK_GPU_SWAP_CHAIN_H

#include <memory>

#include "quack/core/window.h"

#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_adapter.h"
#include "quack/graphics/gpu_context.h"
#include "quack/graphics/gpu_shader_program.h"

namespace Quack {

class GPUShaderProgram;

struct GPUSwapChainDescription {
    std::shared_ptr<Quack::Window> Window;

    std::shared_ptr<GPUContext> Context;
    std::shared_ptr<GPUAdapter> Adapter;
    std::shared_ptr<GPUDevice> Device;

    std::shared_ptr<GPUShaderProgram> Vertex;
    std::shared_ptr<GPUShaderProgram> Fragment;
};

class GPUSwapChain {
public:
    GPUSwapChain(const GPUSwapChainDescription& desc);
    virtual ~GPUSwapChain() = default;

public:
    virtual void Begin() {};
    virtual void End() {};

public:
    const GPUSwapChainDescription& GetDescription() const { return _desc; }

    const std::shared_ptr<GPUContext>& GetContext() const;
    const std::shared_ptr<GPUAdapter>& GetAdapter() const;
    const std::shared_ptr<GPUDevice>& GetDevice() const;
    const std::shared_ptr<Window>& GetWindow() const;

    const std::shared_ptr<GPUShaderProgram>& GetVertex() const;
    const std::shared_ptr<GPUShaderProgram>& GetFragment() const;

protected:
    GPUSwapChainDescription _desc;
};
}

#endif