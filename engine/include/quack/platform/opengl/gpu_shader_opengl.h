#ifndef QUACK_GPU_SHADER_OPENGL_H
#define QUACK_GPU_SHADER_OPENGL_H

#include "quack/graphics/gpu_shader.h"

namespace Quack {
class GPUShaderOpenGL final : public GPUShader {
public:
    explicit GPUShaderOpenGL(const GPUShaderDescription&);
    ~GPUShaderOpenGL() override;

public:
    void Bind() const override;
    void Unbind() const override;

public:
    void UploadUniformInt(const std::string&, int) const override;
    void UploadUniformFloat(const std::string&, float) const override;
    void UploadUniformUnsigned(const std::string&, unsigned) const override;

    void UploadUniformVec2f(const std::string&, const Vector2f&) const override;
    void UploadUniformVec2i(const std::string&, const Vector2i&) const override;
    void UploadUniformVec2u(const std::string&, const Vector2u&) const override;
    void UploadUniformVec2fArray(const std::string&, const std::vector<Vector2f>&) const override;
    void UploadUniformVec2iArray(const std::string&, const std::vector<Vector2i>&) const override;
    void UploadUniformVec2uArray(const std::string&, const std::vector<Vector2u>&) const override;

    void UploadUniformVec3f(const std::string&, const Vector3f&) const override;
    void UploadUniformVec3i(const std::string&, const Vector3i&) const override;
    void UploadUniformVec3u(const std::string&, const Vector3u&) const override;
    void UploadUniformVec3fArray(const std::string&, const std::vector<Vector3f>&) const override;
    void UploadUniformVec3iArray(const std::string&, const std::vector<Vector3i>&) const override;
    void UploadUniformVec3uArray(const std::string&, const std::vector<Vector3u>&) const override;

    void UploadUniformVec4f(const std::string&, const Vector4f&) const override;
    void UploadUniformVec4i(const std::string&, const Vector4i&) const override;
    void UploadUniformVec4u(const std::string&, const Vector4u&) const override;
    void UploadUniformVec4fArray(const std::string&, const std::vector<Vector4f>&) const override;
    void UploadUniformVec4iArray(const std::string&, const std::vector<Vector4i>&) const override;
    void UploadUniformVec4uArray(const std::string&, const std::vector<Vector4u>&) const override;

    void UploadUniformMat2f(const std::string&, const Mat2f&) const override;
    void UploadUniformMat3f(const std::string&, const Mat3f&) const override;
    void UploadUniformMat4f(const std::string&, const Mat4f&) const override;

    void UploadUniformMat2x3f(const std::string&, const Mat2x3f&) const override;
    void UploadUniformMat3x2f(const std::string&, const Mat3x2f&) const override;

    void UploadUniformMat2x4f(const std::string&, const Mat2x4f&) const override;
    void UploadUniformMat4x2f(const std::string&, const Mat4x2f&) const override;

    void UploadUniformMat3x4f(const std::string&, const Mat3x4f&) const override;
    void UploadUniformMat4x3f(const std::string&, const Mat4x3f&) const override;

private:
    void Create();
    void Delete() const;

    void Link() const;
    bool IsLinked() const;

    bool LinkAndCheckStatus() const;

    void AttachPrograms() const;
    void DetachPrograms() const;

    std::string GetInfoLog() const;
    GLint GetUniformLocation(const std::string&) const;
};
}

#endif