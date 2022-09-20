#ifndef QUACK_GPU_BUFFER_OPENGL_H
#define QUACK_GPU_BUFFER_OPENGL_H

#include "quack/graphics/gpu_buffer.h"

namespace Quack {
class GPUBufferOpenGL final : public GPUBuffer {
public:
    GPUBufferOpenGL(const Description &);
    ~GPUBufferOpenGL();

public:
    void Bind() const override;
    void Unbind() const override;
};
}

#endif
