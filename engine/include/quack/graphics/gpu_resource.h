#ifndef QUACK_GPU_RESOURCE_H
#define QUACK_GPU_RESOURCE_H

#include <cstdint>

class GPUResource {
public:
    GPUResource() : _resource(0) {}
    GPUResource(uint32_t resource) : _resource(resource) {}

    virtual ~GPUResource() = default;

public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

public:
    uint32_t GetResource() { return _resource; }

protected:
    uint32_t _resource;
};

#endif