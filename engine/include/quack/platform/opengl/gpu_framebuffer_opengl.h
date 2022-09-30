#ifndef QUACK_GPU_FRAMEBUFFER_OPENGL_H
#define QUACK_GPU_FRAMEBUFFER_OPENGL_H

#include "quack/graphics/gpu_framebuffer.h"

namespace Quack {
class GPUFramebufferOpenGL final : public GPUFramebuffer {
public:
    GPUFramebufferOpenGL(const GPUFramebufferDescription & desc);
    ~GPUFramebufferOpenGL() override;

public:
    void Invalidate() override;
    void Resize(float width, float height) override;

public:
    void Bind() const override;
    void Unbind() const override;
};
}

#endif
