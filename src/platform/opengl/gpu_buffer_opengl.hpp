#ifndef _GPU_BUFFER_OPENGL_
#define _GPU_BUFFER_OPENGL_

#include <iostream>

#include "graphics/gpu_buffer.hpp"

namespace Quack {
class GPUBufferOpenGL : public GPUBuffer {
public:
    GPUBufferOpenGL() : GPUBuffer() {}
    explicit GPUBufferOpenGL(GPUBufferDescription desc) : GPUBuffer(desc) {}

    GPUBufferOpenGL(GPUBufferOpenGL const &) = default;
    GPUBufferOpenGL(GPUBufferOpenGL &&) = default;

    GPUBufferOpenGL & operator=(GPUBufferOpenGL const &) = default;
    GPUBufferOpenGL & operator=(GPUBufferOpenGL &&) = default;

public:
    void Bind() {
        std::cout << "Buffer were binded!\n";
    }
    void Unbind() {
        std::cout << "Buffer were unbinded!\n";
    }
};
}

#endif