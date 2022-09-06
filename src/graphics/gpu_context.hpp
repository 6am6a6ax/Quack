class GPUDevice;

class GPUContext {
public:
    virtual ~GPUContext();

protected:
    GPUContext(GPUDevice * device) {}

public:
    GPUDevice * GetDevice() const;

private:
    GPUDevice * _device;
};