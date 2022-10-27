#ifndef QUACK_GPU_SHADER_PROGRAM_DESCRIPTION_H
#define QUACK_GPU_SHADER_PROGRAM_DESCRIPTION_H

#include <string>

#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_shader_program.h"

namespace Quack {
enum class ShaderProgramType {
    Vertex, Fragment
};

struct GPUShaderProgramDescription {
    std::string Name;
    std::string Source;
    ShaderProgramType Type;

    std::shared_ptr<GPUDevice> Device;
};
}

#endif