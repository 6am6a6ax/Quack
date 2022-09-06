#ifndef _GPU_TEXTURE_
#define _GPU_TEXTURE_

#include "gpu_texture_description.hpp"

namespace Quack {
class GPUTexture {
public:
    virtual GPUTexture() {}

public:
    GPUTextureDescription GetDescription() const {}

private:
    GPUTextureDescription _Description;
};
}

#endif