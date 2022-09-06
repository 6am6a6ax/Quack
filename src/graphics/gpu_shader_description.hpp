#ifndef _GPU_SHADER_DESCRIPTION_
#define _GPU_SHADER_DESCRIPTION_

#include <vector>

#include "gpu_shader_program.hpp"

namespace Quack {
class GPUShaderDescription {
public:
    virtual GPUShaderDescription() {}

public:
    std::vector<GPUShaderProgram> GetShaderPrograms() {}
};
}

#endif