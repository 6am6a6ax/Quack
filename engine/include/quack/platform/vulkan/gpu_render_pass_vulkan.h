#ifndef QUACK_GPU_RENDER_PASS_VULKAN_H
#define QUACK_GPU_RENDER_PASS_VULKAN_H

#include <vulkan/vulkan_core.h>

namespace Quack {
class GPURenderPassVulkan final : public GPURenderPass {
public:
    explicit GPURenderPassVulkan(const GPURenderPassDescription&);
    ~GPURenderPassVulkan() override;

public:
    void Begin(uint32_t index);
    void End();

public:
    const VkRenderPass& GetRenderPass() const;

private:
    void Init();
    void Create();

private:
    void InitColorAttachmentDescription();
    void InitColorAttachmentReference();
    
    void InitSubpassDescription();
    void InitSubpassDependency();

    void InitRenderPass();
    void CreateRenderPass();

private:
    VkAttachmentDescription _colorAttachmentDescription;
    VkAttachmentReference _colorAttachmentReference;

    VkSubpassDescription _subpassDescription;
    VkSubpassDependency _subpassDependency;

    VkRenderPass _renderPass;
    VkRenderPassCreateInfo _renderPassInfo;
};
}

#endif