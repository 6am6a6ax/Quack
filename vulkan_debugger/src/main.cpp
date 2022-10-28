#include <quack/quack.h>

int main() {
    Quack::WindowDescription windowDesc{};
    windowDesc.WindowSize = { 1280, 720 };
    windowDesc.Title = "Vulkan Debugger";
    const auto window = std::static_pointer_cast<Quack::Window>(std::make_shared<Quack::WindowGLFW>(windowDesc));

    Quack::GPUContext::Description gpuContextDesc{};
    gpuContextDesc.Window = window;
    gpuContextDesc.isValidationLayersEnabled = true;
    const auto gpuContext = 
        std::static_pointer_cast<Quack::GPUContext>(std::make_shared<Quack::GPUContextVulkan>(gpuContextDesc));

    Quack::GPUAdapterDescription gpuAdapterDesc{};
    gpuAdapterDesc.Context = gpuContext;
    const auto gpuAdapter = 
        std::static_pointer_cast<Quack::GPUAdapter>(std::make_shared<Quack::GPUAdapterVulkan>(gpuAdapterDesc));

    Quack::GPUDeviceDescription gpuDeviceDesc{};
    gpuDeviceDesc.Adapter = gpuAdapter;
    gpuDeviceDesc.Context = gpuContext;
    const auto gpuDevice =
        std::static_pointer_cast<Quack::GPUDevice>(std::make_shared<Quack::GPUDeviceVulkan>(gpuDeviceDesc));

    // // Quack::GPURenderPassDescription gpuRenderPassDesc{};
    // // gpuRenderPassDesc.Context = gpuContext;
    // // gpuRenderPassDesc.Device = gpuDevice;
    // // Quack::GPURenderPass* gpuRenderPass = new Quack::GPURenderPassVulkan(gpuRenderPassDesc);


    Quack::GPUShaderProgramDescription gpuVertexShaderProgramDesc{};
    gpuVertexShaderProgramDesc.Name = "/home/bujhm/dev/cpp/cg/quack/vulkan_demo/shaders/vert.spv";
    gpuVertexShaderProgramDesc.Device = gpuDevice;
    //gpuVertexShaderProgramDesc.Source;
    //gpuVertexShaderProgramDesc.Type;
    const auto vertexShaderProgram =
        std::static_pointer_cast<Quack::GPUShaderProgram>(std::make_shared<Quack::GPUShaderProgramVulkan>(gpuVertexShaderProgramDesc));

    Quack::GPUShaderProgramDescription gpuFragShaderProgramDesc{};
    gpuFragShaderProgramDesc.Name = "/home/bujhm/dev/cpp/cg/quack/vulkan_demo/shaders/frag.spv";
    gpuFragShaderProgramDesc.Device = gpuDevice;
    //gpuFragShaderProgramDesc.Source;
    //gpuFragShaderProgramDesc.Type;
    const auto fragShaderProgram =
        std::static_pointer_cast<Quack::GPUShaderProgram>(std::make_shared<Quack::GPUShaderProgramVulkan>(gpuFragShaderProgramDesc));


    Quack::GPUSwapChainDescription gpuSwapChainDesc{};
    gpuSwapChainDesc.Adapter = gpuAdapter;
    gpuSwapChainDesc.Context = gpuContext;
    gpuSwapChainDesc.Device = gpuDevice;
    gpuSwapChainDesc.Window = window;
    gpuSwapChainDesc.Vertex = vertexShaderProgram;
    gpuSwapChainDesc.Fragment = fragShaderProgram;
    const auto gpuSwapChain = 
        std::static_pointer_cast<Quack::GPUSwapChain>(std::make_shared<Quack::GPUSwapChainVulkan>(gpuSwapChainDesc));


    // Quack::GPUCommandBufferDescription gpuCommandBufferDesc{};
    // gpuCommandBufferDesc.Context = gpuContext;
    // gpuCommandBufferDesc.Device = gpuDevice;
    // gpuCommandBufferDesc.Adapter = gpuAdapter;
    // Quack::GPUCommandBuffer* gpuCommandBuffer = new Quack::GPUCommandBuffer(gpuCommandBufferDesc);

    // Quack::GPUPipelineDescription gpuPipelineDesc{};
    // gpuPipelineDesc.CommandBuffer = gpuCommandBuffer;
    // gpuPipelineDesc.Vertex = vertexShaderProgram;
    // gpuPipelineDesc.Fragment = fragShaderProgram;
    // // gpuPipelineDesc.RenderPass = gpuRenderPass;
    // gpuPipelineDesc.SwapChain = gpuSwapChain;
    // gpuPipelineDesc.Context = gpuContext;
    // gpuPipelineDesc.Device = gpuDevice;
    // Quack::GPUPipeline* gpuPipeline = new Quack::GPUPipelineVulkan(gpuPipelineDesc);

    Quack::ApplicationDescription appDesc{};
    appDesc.Window = window;
    // appDesc.GPUContext = gpuContext;
    // appDesc.SwapChain = gpuSwapChain;
    // appDesc.GPUDevice = gpuDevice;
    // appDesc.Camera = new Quack::CameraPerspective();

    Quack::Application::GetInstance().Init(appDesc);

    try {
        while(true) {
            glfwPollEvents();
            std::dynamic_pointer_cast<Quack::GPUSwapChainVulkan>(gpuSwapChain)->BeginFrame();
            std::dynamic_pointer_cast<Quack::GPUSwapChainVulkan>(gpuSwapChain)->DrawFrame();
            std::dynamic_pointer_cast<Quack::GPUSwapChainVulkan>(gpuSwapChain)->EndFrame();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}