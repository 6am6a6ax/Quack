#ifndef QUACK_GPU_SHADER_PROGRAM_DESCRIPTION_H
#define QUACK_GPU_SHADER_PROGRAM_DESCRIPTION_H

#include <string>

#include "quack/graphics/gpu_device.h"

namespace Quack {
enum class ShaderProgramType {
    Vertex, Fragment
};

struct GPUShaderProgramDescription {
    std::string Name;
    std::string Source;
    ShaderProgramType Type;

    GPUDevice* Device;
};
}

#endif