#ifndef _GPU_BUFFER_OPENGL_
#define _GPU_BUFFER_OPENGL_

#include <iostream>

#include "graphics/gpu_buffer.hpp"

namespace Quack {
class GPUBufferOpenGL final : public GPUBuffer {
public:
    GPUBufferOpenGL() : GPUBuffer() {}
    explicit GPUBufferOpenGL(GPUBufferDescription desc) : GPUBuffer(desc) {}

    GPUBufferOpenGL(GPUBufferOpenGL const &) = default;
    GPUBufferOpenGL(GPUBufferOpenGL &&) = default;

    GPUBufferOpenGL & operator=(GPUBufferOpenGL const &) = default;
    GPUBufferOpenGL & operator=(GPUBufferOpenGL &&) = default;

public:
    ~GPUBufferOpenGL() final = default;

public:
    virtual void Bind() final {
        std::cout << "Buffer were binded!\n";
    }

    virtual void Unbind() final {
        std::cout << "Buffer were unbinded!\n";
    }
};
}

#endif