#ifndef QUACK_GPU_SHADER_H
#define QUACK_GPU_SHADER_H

#include <vector>

#include "quack/math/math.h"
#include "quack/graphics/gpu_resource.h"
#include "quack/graphics/gpu_shader_program.h"

namespace Quack {
struct GPUShaderDescription {
    GPUShaderProgram* VertexShader;
    GPUShaderProgram* GeometryShader;
    GPUShaderProgram* FragmentShader;
};

class GPUShader : public GPUResource {
public:
    explicit GPUShader(const GPUShaderDescription& desc) : _desc(desc) {}
    ~GPUShader() override = default;

public:
    virtual void UploadUniformInt(const std::string&, int) const = 0;
    virtual void UploadUniformFloat(const std::string&, float) const = 0;
    virtual void UploadUniformUnsigned(const std::string&, unsigned) const = 0;

    virtual void UploadUniformVec2f(const std::string&, const Vector2f&) const = 0;
    virtual void UploadUniformVec2i(const std::string&, const Vector2i&) const = 0;
    virtual void UploadUniformVec2u(const std::string&, const Vector2u&) const = 0;
    virtual void UploadUniformVec2fArray(const std::string&, const std::vector<Vector2f>&) const = 0;
    virtual void UploadUniformVec2iArray(const std::string&, const std::vector<Vector2i>&) const = 0;
    virtual void UploadUniformVec2uArray(const std::string&, const std::vector<Vector2u>&) const = 0;

    virtual void UploadUniformVec3f(const std::string&, const Vector3f&) const = 0;
    virtual void UploadUniformVec3i(const std::string&, const Vector3i&) const = 0;
    virtual void UploadUniformVec3u(const std::string&, const Vector3u&) const = 0;
    virtual void UploadUniformVec3fArray(const std::string&, const std::vector<Vector3f>&) const = 0;
    virtual void UploadUniformVec3iArray(const std::string&, const std::vector<Vector3i>&) const = 0;
    virtual void UploadUniformVec3uArray(const std::string&, const std::vector<Vector3u>&) const = 0;

    virtual void UploadUniformVec4f(const std::string&, const Vector4f&) const = 0;
    virtual void UploadUniformVec4i(const std::string&, const Vector4i&) const = 0;
    virtual void UploadUniformVec4u(const std::string&, const Vector4u&) const = 0;
    virtual void UploadUniformVec4fArray(const std::string&, const std::vector<Vector4f>&) const = 0;
    virtual void UploadUniformVec4iArray(const std::string&, const std::vector<Vector4i>&) const = 0;
    virtual void UploadUniformVec4uArray(const std::string&, const std::vector<Vector4u>&) const = 0;

    virtual void UploadUniformMat2f(const std::string&, const Mat2f&) const = 0;
    virtual void UploadUniformMat3f(const std::string&, const Mat3f&) const = 0;
    virtual void UploadUniformMat4f(const std::string&, const Mat4f&) const = 0;

    virtual void UploadUniformMat2x3f(const std::string&, const Mat2x3f&) const = 0;
    virtual void UploadUniformMat3x2f(const std::string&, const Mat3x2f&) const = 0;

    virtual void UploadUniformMat2x4f(const std::string&, const Mat2x4f&) const = 0;
    virtual void UploadUniformMat4x2f(const std::string&, const Mat4x2f&) const = 0;

    virtual void UploadUniformMat3x4f(const std::string&, const Mat3x4f&) const = 0;
    virtual void UploadUniformMat4x3f(const std::string&, const Mat4x3f&) const = 0;

public:
    const GPUShaderDescription& GetDescription() const;
    void SetDescription(const GPUShaderDescription&);

protected:
    GPUShaderDescription _desc;
};
}

#endif