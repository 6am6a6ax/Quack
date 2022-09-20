#ifndef QUACK_GPU_SHADER_PROGRAM_OPENGL_H
#define QUACK_GPU_SHADER_PROGRAM_OPENGL_H

#include "quack/graphics/gpu_shader_program.h"

namespace Quack {
class GPUShaderProgramOpenGL : public GPUShaderProgram {
public:
    GPUShaderProgramOpenGL(const GPUShaderProgramDescription &);
    ~GPUShaderProgramOpenGL();

public:
    void Bind() const override;
    void Unbind() const override;
};
}

#endif
