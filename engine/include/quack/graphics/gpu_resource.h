#ifndef QUACK_GPU_RESOURCE_H
#define QUACK_GPU_RESOURCE_H

class GPUResource {
public:
    GPUResource() = default;
    GPUResource(unsigned resource) : _resource(resource) {}

    virtual ~GPUResource() = default;

public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

public:
    unsigned GetResource() { return _resource; }
    void SetResource(unsigned resource) { _resource = resource; }

protected:
    unsigned _resource;
};

#endif