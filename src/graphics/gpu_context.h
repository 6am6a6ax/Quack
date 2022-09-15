#ifndef _GPU_CONTEXT_
#define _GPU_CONTEXT_

#include "gpu_device.hpp"

namespace Quack {
class GPUContext {
public:
    virtual ~GPUContext() {}

protected:
    GPUContext(GPUDevice * device) {}

public:
    GPUDevice * GetDevice() const {}

private:
    GPUDevice * _device;
};
}

#endif