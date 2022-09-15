#ifndef QUACK_GPU_CONTEXT_H
#define QUACK_GPU_CONTEXT_H

#include "gpu_device.h"

namespace Quack {
class GPUContext {
public:
    explicit GPUContext(GPUDevice & device);

    virtual ~GPUContext();

public:
    const GPUDevice * GetDevice() const;

private:
    GPUDevice * _device;
};
}

#endif