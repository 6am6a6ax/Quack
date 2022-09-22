#ifndef QUACK_GPU_FRAMEBUFFER_H
#define QUACK_GPU_FRAMEBUFFER_H

#include "quack/graphics/gpu_resource.h"

namespace Quack {
struct GPUFramebufferDescription {
    uint32_t Samples = 0;
    struct Size {
        uint32_t Width;
        uint32_t Height;
    } FrameSize;
    bool SwapChainTarget = false;
    uint32_t ColorAttachment;
    uint32_t DepthAttachment;
};

class GPUFramebuffer : public GPUResource {
public:
    GPUFramebuffer(const GPUFramebufferDescription & desc) : _desc(desc) {}
    virtual ~GPUFramebuffer() = default;

public:
    virtual void Invalidate() = 0;

public:
    const GPUFramebufferDescription & GetDescription() const { return _desc; }
    void SetDescription(const GPUFramebufferDescription & desc) { _desc = desc; }

    const GPUFramebufferDescription::Size & GetSize() const { return _desc.FrameSize; }
    void SetSize(const GPUFramebufferDescription::Size & frameSize) { _desc.FrameSize = frameSize; }

    const uint32_t GetSamples() const { return _desc.Samples; }
    void SetSamples(const uint32_t & samples) { _desc.Samples = samples; }

    const uint32_t & GetColorAttachment() const { return _desc.ColorAttachment; }
    void SetColorAttachment(const uint32_t & colorAttachment) { _desc.ColorAttachment = colorAttachment; }

    const uint32_t & GetDepthAttachment() const { return _desc.DepthAttachment; }
    void SetDepthAttachment(const uint32_t & depthAttachment) { _desc.DepthAttachment = depthAttachment; }

protected:
    GPUFramebufferDescription _desc;
};
}

#endif
