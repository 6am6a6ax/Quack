#ifndef QUACK_GPU_TEXTURE_H
#define QUACK_GPU_TEXTURE_H

#include "quack/graphics/gpu_resource.h"

#include "gpu_texture_description.h"

namespace Quack {
class GPUTexture : public GPUResource {
public:
    GPUTexture(const GPUTextureDescription & desc) : _desc(desc) {}
public:
    const GPUTextureDescription & GetDescription() const { return _desc; }

    const uint32_t & GetWidth() const { return _desc.Width; }
    void SetWidth(const uint32_t & width) { _desc.Width = width; }

    const uint32_t & GetHeight() const { return _desc.Height; }
    void SetHeight(const uint32_t & height) { _desc.Height = height; }

protected:
    GPUTextureDescription _desc;
};
}

#endif