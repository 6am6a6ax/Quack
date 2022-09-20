#ifndef _GPU_TEXTURE_DESCRIPTION_
#define _GPU_TEXTURE_DESCRIPTION_

#include <cstdint>
#include <string>

namespace Quack {
struct GPUTextureDescription {
    uint32_t Width;
    uint32_t Height;

    std::string Path;
};
}

#endif