#ifndef QUACK_GPU_CONTEXT_H
#define QUACK_GPU_CONTEXT_H

namespace Quack {
class GPUContext {
public:
    virtual ~GPUContext() = default;

public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};
}

#endif