#ifndef QUACK_GPU_SHADER_PROGRAM_H
#define QUACK_GPU_SHADER_PROGRAM_H

#include <string>

#include "gpu_resource.h"
#include "gpu_shader_program_description.h"

namespace Quack {
class GPUShaderProgram : public GPUResource  {
public:
    GPUShaderProgram(const GPUShaderProgramDescription & desc);
    virtual ~GPUShaderProgram() = default;

public:
    const GPUShaderProgramDescription & GetDescription() const;
    const std::shared_ptr<GPUDevice>& GetDevice() const;

protected:
    GPUShaderProgramDescription _desc;
};
}

#endif