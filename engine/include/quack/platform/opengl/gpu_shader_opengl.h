#ifndef QUACK_GPU_SHADER_OPENGL_H
#define QUACK_GPU_SHADER_OPENGL_H

#include "quack/graphics/gpu_shader.h"

namespace Quack {
class GPUShaderOpenGL final : public GPUShader {
public:
    GPUShaderOpenGL(const GPUShaderDescription &);
    ~GPUShaderOpenGL();

public:
    void Bind() const override;
    void Unbind() const override;
};
}

#endif
