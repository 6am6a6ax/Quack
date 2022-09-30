#ifndef _GPU_SHADER_
#define _GPU_SHADER_

#include "gpu_resource.h"
#include "gpu_shader_description.h"

#include "quack/math/math.h"

namespace Quack {
class GPUShader : public GPUResource {
public:
    GPUShader(const GPUShaderDescription & desc) : _desc(desc) {}
    virtual ~GPUShader() {}

    virtual void UploadUniformMat4(const std::string &, const Mat4f &) = 0;
    virtual void UploadUniformInt(const std::string &, int) = 0;
    virtual void UploadUniformVec4(const std::string &, const Vector4f &) = 0;

public:
    const GPUShaderDescription & GetDescription() const;

protected:
    GPUShaderDescription _desc;
};
}

#endif