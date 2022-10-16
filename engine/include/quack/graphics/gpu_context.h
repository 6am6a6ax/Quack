#ifndef QUACK_GPU_CONTEXT_H
#define QUACK_GPU_CONTEXT_H

#include "quack/core/window.h"

namespace Quack {
class GPUContext {
public:
    struct Desciption {
    };

public:
    GPUContext() = default;
    // GPUContext(const Desciption& desc);
    virtual ~GPUContext() = default;

public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

public:
    const Desciption& GetDescription() const;
    void SetDescription(const Desciption& desc);

protected:
    Desciption _desc;
};
}

#endif