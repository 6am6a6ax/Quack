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

public:
    void UploadUniformMat4(const std::string &, const Mat4f &) override;
    void UploadUniformInt(const std::string &, int) override;
    void UploadUniformVec4(const std::string &, const Vector4f &) override;
};
}

#endif
