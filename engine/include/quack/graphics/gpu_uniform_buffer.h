#ifndef QUACK_GPU_UNIFORM_BUFFER_H
#define QUACK_GPU_UNIFORM_BUFFER_H

#include "quack/graphics/gpu_resource.h"

namespace Quack {
class GPUUniformBuffer : public GPUResource {
public:
    ~GPUUniformBuffer() override {}

public:
    void Bind() const override {}
    void Unbind() const override {}
};
}

#endif 