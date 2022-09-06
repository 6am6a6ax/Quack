#ifndef _GPU_DEVICE_
#define _GPU_DEVICE_

class GPUBuffer;
class GPUTexure;
class GPUShader;
class GPUShaderProgram;
class GPUPipelineState;

class GPUAdapter;

namespace Quack {
class GPUDevice {
public:
    virtual ~GPUDevice() {}

public:
    virtual GPUBuffer * CreateBuffer() = 0;
    virtual GPUTexure * CreateTexture() = 0;
    virtual GPUShader * CreateShader() = 0;
    virtual GPUShaderProgram * CreateShaderProgram() = 0;
    virtual GPUPipelineState * CreatePipelineState() = 0;

public:
    virtual GPUAdapter * GetAdapter() const = 0;
};
}

#endif