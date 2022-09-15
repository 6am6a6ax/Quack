#ifndef _GPU_RESOURCE_
#define _GPU_RESOURCE_

#include <cstdint>

class GPUResource {
public:
    GPUResource() : _resource(0) {}
    GPUResource(uint32_t resource) : _resource(resource) {}

    GPUResource(GPUResource const &) = default;
    GPUResource(GPUResource &) = default;

    GPUResource & operator=(GPUResource const &) = default;
    GPUResource & operator=(GPUResource &) = default;

public:
    virtual ~GPUResource() = default;

public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

public:
    uint32_t GetResource() { return _resource; }

protected:
    uint32_t _resource;
};

#endif