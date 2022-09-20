#ifndef GPU_ADAPTER_H
#define GPU_ADAPTER_H

#include <string>
#include <cstdint>

namespace Quack {
class GPUAdapter {
public:
    virtual ~GPUAdapter() = default;

public:
    virtual bool IsValid() const = 0;
    virtual const uint32_t & GetVendorId() const = 0;
    virtual const std::string & GetDescription() const = 0;
};
}

#endif