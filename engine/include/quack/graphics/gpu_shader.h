#ifndef _GPU_SHADER_
#define _GPU_SHADER_

#include "gpu_resource.h"
#include "gpu_shader_description.h"

namespace Quack {
class GPUShader : public GPUResource {
public:
    GPUShader(const GPUShaderDescription & desc) : _desc(desc) {}
    virtual ~GPUShader() {}

public:
    const GPUShaderDescription & GetDescription() const;

protected:
    GPUShaderDescription _desc;
};
}

#endif