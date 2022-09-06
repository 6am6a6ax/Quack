#ifndef _GPU_ADAPTER_
#define _GPU_ADAPTER_

#include <cstdint>
#include <string>

namespace Quack {
class GPUAdapter {
public:
    virtual ~GPUAdapter() {}

public:
    virtual bool IsValid() const = 0;
    virtual uint32_t GetVendorId() const = 0;
    virtual std::string GetDescription() const = 0;
};
}

#endif