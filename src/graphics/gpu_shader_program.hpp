#ifndef _GPU_SHADER_PROGRAM_
#define _GPU_SHADER_PROGRAM_

#include <string>

#include "gpu_shader_program_description.hpp"

namespace Quack {
class GPUShaderProgram {
public:
    virtual ~GPUShaderProgram() {}

public:
    GPUShaderProgramDescription GetDescription() const {}

private:
    GPUShaderProgramDescription _Description;
};
}

#endif