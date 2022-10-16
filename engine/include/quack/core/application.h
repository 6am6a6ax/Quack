#ifndef QUACK_APPLICATION_H
#define QUACK_APPLICATION_H

#include "quack/core/asset_library.h"
#include "quack/core/event.h"
#include "quack/core/timestep.h"
#include "quack/core/window.h"

#include "quack/graphics/gpu_context.h"
#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_framebuffer.h"
#include "quack/render/renderer.h"
#include "quack/render/camera.h"

#include "quack/scene/scene.h"

namespace Quack {
struct ApplicationDescription {
    std::shared_ptr<Quack::Window> Window;
    std::shared_ptr<Quack::GPUDevice> GPUDevice;
    std::shared_ptr<Quack::LayerStack> LayerStack;
    std::shared_ptr<Quack::AssetLibrary> AssetLibrary;
    std::shared_ptr<Quack::Scene> Scene;
    std::shared_ptr<Quack::Camera> Camera;
    std::shared_ptr<Quack::GPUFramebuffer> framebuffer;
};

class Application {
    Application() = default;

public:
    static Application & GetInstance();
    virtual ~Application() = default;

public:
    Application(const Application &) = delete;
    Application & operator=(const Application &) = delete;

public:
    void Init(const ApplicationDescription &);
    void Run();

public:
    void OnUpdate();
    void OnEvent(Event &);

public:
    float GetTime() const;

public:
    const ApplicationDescription & GetDescription();
    void SetDescription(const ApplicationDescription &);

    std::shared_ptr<Window> GetWindow();
    void SetWindow(std::shared_ptr<Window>);

    std::shared_ptr<GPUDevice> GetDevice();
    void SetDevice(std::shared_ptr<GPUDevice>);

    std::shared_ptr<LayerStack> GetLayerStack();
    void SetLayerStack(std::shared_ptr<LayerStack>);

    std::shared_ptr<Scene> GetScene();
    void SetScene(std::shared_ptr<Scene>);

    std::shared_ptr<AssetLibrary> GetAssetLibrary() const { return _desc.AssetLibrary; }
    void SetAssetLibrary(std::shared_ptr<AssetLibrary> assetLibrary) { _desc.AssetLibrary = assetLibrary; }

    std::shared_ptr<Camera> GetCamera() const { return _desc.Camera; }

    const Timestep& GetTimestep() const;

    GPUContext* GetContext() const;

private:
    void BindBaseCallbackAndLayerStack();

private:
    ApplicationDescription _desc;

    Timestep _timestep;
};
}

#endif