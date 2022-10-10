#ifndef QUACK_GPU_VERTEX_ARRAY_OPENGL_H
#define QUACK_GPU_VERTEX_ARRAY_OPENGL_H

#include "quack/graphics/gpu_vertex_array.h"
#include <memory>

namespace Quack {
class GPUVertexArrayOpenGL final : public GPUVertexArray {
public:
    GPUVertexArrayOpenGL();
    ~GPUVertexArrayOpenGL() override;

public:
    void Bind() const override;
    void Unbind() const override;

public:
    void AddBuffer(std::shared_ptr<GPUBuffer>) override;

private:
    void SetBufferLayout(const GPUBuffer::Layout &) override;
};
}

#endif
