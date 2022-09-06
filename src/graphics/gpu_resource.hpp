class GPUResource {
public:
    virtual ~GPUResource();

public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

public:
    virtual unsigned int GetResource() = 0;

protected:
    unsigned int _resource;
};