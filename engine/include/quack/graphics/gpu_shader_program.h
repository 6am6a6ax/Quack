#ifndef _GPU_SHADER_PROGRAM_
#define _GPU_SHADER_PROGRAM_

#include <string>

#include "gpu_shader_program_description.h"
#include "gpu_resource.h"

namespace Quack {
class GPUShaderProgram : public GPUResource  {
public:
    GPUShaderProgram(const GPUShaderProgramDescription & desc) : _desc(desc) {}
    virtual ~GPUShaderProgram() = default;

public:
    const GPUShaderProgramDescription & GetDescription() const { return _desc;}

protected:
    GPUShaderProgramDescription _desc;
};
}

#endif