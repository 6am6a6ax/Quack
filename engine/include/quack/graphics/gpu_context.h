#ifndef QUACK_GPU_CONTEXT_H
#define QUACK_GPU_CONTEXT_H

#include "quack/core/window.h"

namespace Quack {
class GPUContext {
public:
    struct Description {
        std::shared_ptr<Quack::Window> Window;
        bool isValidationLayersEnabled = false;
    };

public:
    GPUContext(const GPUContext::Description& desc);
    virtual ~GPUContext() = default;

public:
    virtual void Init() {};
    virtual void SwapBuffers() {};

public:
    const Description& GetDescription() const;
    const std::shared_ptr<Window>& GetWindow() const;

private:
    Description _desc;
};
}

#endif