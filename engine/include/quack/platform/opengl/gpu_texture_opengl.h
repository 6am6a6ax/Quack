#ifndef QUACK_GPU_TEXTURE_OPENGL_H
#define QUACK_GPU_TEXTURE_OPENGL_H

#include "quack/graphics/gpu_texture.h"

namespace Quack {
class GPUTextureOpenGL final : public GPUTexture {
public:
    GPUTextureOpenGL(const GPUTextureDescription & desc);
    ~GPUTextureOpenGL() override;

public:
    void Bind() const override;
    void Unbind() const override;
};
}

#endif
