#ifndef GPU_ADAPTER_H
#define GPU_ADAPTER_H

#include "quack/graphics/gpu_context.h"

namespace Quack {
struct GPUAdapterDescription {
    std::shared_ptr<GPUContext> Context;
};

class GPUAdapter {
public:
    GPUAdapter(const GPUAdapterDescription& desc);
    virtual ~GPUAdapter() = default;

public:
    const GPUAdapterDescription& GetDescription() const;

public:
    const std::shared_ptr<GPUContext>& GetContext() const;

private:
    GPUAdapterDescription _desc;
};
}

#endif