#ifndef QUACK_GPU_CONTEXT_H
#define QUACK_GPU_CONTEXT_H

#include "quack/core/window.h"

namespace Quack {
class GPUContext {
public:
    struct Description {
        Quack::Window* Window;
    };

public:
    GPUContext(const GPUContext::Description& desc) : _desc(desc) {}
    virtual ~GPUContext() = default;

public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

public:
    const Description& GetDescription() const;
    void SetDescription(const Description& desc);

    Window* GetWindow() const { return _desc.Window; }

protected:
    Description _desc;
};
}

#endif