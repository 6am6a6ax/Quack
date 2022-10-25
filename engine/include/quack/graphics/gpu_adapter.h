#ifndef GPU_ADAPTER_H
#define GPU_ADAPTER_H

#include "quack/graphics/gpu_context.h"

namespace Quack {
struct GPUAdapterDescription {
    GPUContext* Context;
};

class GPUAdapter {
public:
    GPUAdapter(const GPUAdapterDescription& desc) : _desc(desc) {}
    virtual ~GPUAdapter() = default;

public:
    const GPUAdapterDescription& GetDescription() const { return _desc; }

public:
    GPUContext* GetContext() const { return _desc.Context; }

private:
    GPUAdapterDescription _desc;
};
}

#endif