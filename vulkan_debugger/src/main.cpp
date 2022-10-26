#include "quack/graphics/gpu_pipeline.h"
#include "quack/graphics/gpu_render_pass.h"
#include <quack/quack.h>

int main() {
    Quack::WindowDescription windowDesc{};
    windowDesc.WindowSize = { 1280, 720 };
    windowDesc.Title = "Vulkan Debugger";

    Quack::Window* window = new Quack::WindowGLFW(windowDesc);

    Quack::GPUContext::Description gpuContextDesc{};
    gpuContextDesc.Window = window;
    Quack::GPUContext* gpuContext = new Quack::GPUContextVulkan(gpuContextDesc);

    Quack::GPUAdapter* gpuAdapter = new Quack::GPUAdapterVulkan({gpuContext});

    Quack::GPUDeviceDescription gpuDeviceDesc{};
    gpuDeviceDesc.Adapter = gpuAdapter;
    gpuDeviceDesc.Context = gpuContext;
    Quack::GPUDevice* gpuDevice = new Quack::GPUDeviceVulkan(gpuDeviceDesc);

    // Quack::GPURenderPassDescription gpuRenderPassDesc{};
    // gpuRenderPassDesc.Context = gpuContext;
    // gpuRenderPassDesc.Device = gpuDevice;
    // Quack::GPURenderPass* gpuRenderPass = new Quack::GPURenderPassVulkan(gpuRenderPassDesc);

    Quack::GPUSwapChainDescription gpuSwapChainDesc{};
    gpuSwapChainDesc.Adapter = gpuAdapter;
    gpuSwapChainDesc.CommandBuffer = nullptr;
    gpuSwapChainDesc.Context = gpuContext;
    gpuSwapChainDesc.Device = gpuDevice;
    // gpuSwapChainDesc.RenderPass = gpuRenderPass;
    Quack::GPUSwapChain* gpuSwapChain = new Quack::GPUSwapChainVulkan(gpuSwapChainDesc);

    Quack::GPUShaderProgramDescription gpuVertexShaderProgramDesc{};
    gpuVertexShaderProgramDesc.Name = "/home/bujhm/dev/cpp/cg/quack/vulkan_demo/shaders/vert.spv";
    gpuVertexShaderProgramDesc.Device = gpuDevice;
    //gpuVertexShaderProgramDesc.Source;
    //gpuVertexShaderProgramDesc.Type;
    Quack::GPUShaderProgram* vertexShaderProgram = new Quack::GPUShaderProgramVulkan(gpuVertexShaderProgramDesc);

    Quack::GPUShaderProgramDescription gpuFragShaderProgramDesc{};
    gpuFragShaderProgramDesc.Name = "/home/bujhm/dev/cpp/cg/quack/vulkan_demo/shaders/frag.spv";
    gpuFragShaderProgramDesc.Device = gpuDevice;
    //gpuFragShaderProgramDesc.Source;
    //gpuFragShaderProgramDesc.Type;
    Quack::GPUShaderProgram* fragShaderProgram = new Quack::GPUShaderProgramVulkan(gpuFragShaderProgramDesc);

    Quack::GPUCommandBufferDescription gpuCommandBufferDesc{};
    gpuCommandBufferDesc.Context = gpuContext;
    gpuCommandBufferDesc.Device = gpuDevice;
    gpuCommandBufferDesc.Adapter = gpuAdapter;
    Quack::GPUCommandBuffer* gpuCommandBuffer = new Quack::GPUCommandBuffer(gpuCommandBufferDesc);

    Quack::GPUPipelineDescription gpuPipelineDesc{};
    gpuPipelineDesc.CommandBuffer = gpuCommandBuffer;
    gpuPipelineDesc.Vertex = vertexShaderProgram;
    gpuPipelineDesc.Fragment = fragShaderProgram;
    // gpuPipelineDesc.RenderPass = gpuRenderPass;
    gpuPipelineDesc.SwapChain = gpuSwapChain;
    gpuPipelineDesc.Context = gpuContext;
    gpuPipelineDesc.Device = gpuDevice;
    Quack::GPUPipeline* gpuPipeline = new Quack::GPUPipelineVulkan(gpuPipelineDesc);

    Quack::ApplicationDescription appDesc{};
    appDesc.Window = window;
    appDesc.GPUContext = gpuContext;
    appDesc.SwapChain = gpuSwapChain;
    appDesc.GPUDevice = gpuDevice;
    // // appDesc.GPUDevice = new Quack::GPUDeviceVulkan();
    // // appDesc.Camera = new Quack::CameraPerspective();

    Quack::Application::GetInstance().Init(appDesc);

    try {
        while(true) {
            gpuSwapChain->Begin();

            // Quack::Renderer::RenderVk(dynamic_cast<Quack::GPUCommandBufferVulkan*>(gpuCommandBuffer), 
            //                           dynamic_cast<Quack::GPURenderPassVulkan*>(gpuRenderPass), 
            //                           dynamic_cast<Quack::GPUPipelineVulkan*>(gpuPipeline));

            gpuSwapChain->End();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}