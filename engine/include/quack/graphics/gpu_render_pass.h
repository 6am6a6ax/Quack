#ifndef QUACK_GPU_RENDER_PASS_H
#define QUACK_GPU_RENDER_PASS_H

namespace Quack {
struct GPURenderPassDescription {

};

class GPURenderPass {
public:
    GPURenderPass(const GPURenderPassDescription& desc) : _desc(desc) {}
    virtual ~GPURenderPass() = default;

public:
    const GPURenderPassDescription& GetDescription() const { return _desc; }
    
private:
    GPURenderPassDescription _desc;
};
}

#endif