#ifndef QUACK_APPLICATION_H
#define QUACK_APPLICATION_H

#include "quack/core/asset_library.h"
#include "quack/core/event.h"
#include "quack/core/timestep.h"
#include "quack/core/window.h"

#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_framebuffer.h"
#include "quack/render/renderer.h"
#include "quack/render/camera.h"

#include "quack/scene/scene.h"

namespace Quack {
struct ApplicationDescription {
    std::shared_ptr<Quack::Window> Window;
    std::shared_ptr<Quack::GPUDevice> GPUDevice;
    std::shared_ptr<Quack::LayerStack> yerStack;
    std::shared_ptr<Quack::AssetLibrary> setLibrary;
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

    Window * GetWindow();
    void SetWindow(Window *);

    GPUDevice * GetDevice();
    void SetDevice(GPUDevice *);

    LayerStack & GetLayerStack();
    void SetLayerStack(const LayerStack &);

    Scene * GetScene();
    void SetScene(Scene *);

    AssetLibrary GetAssetLibrary() const { return _desc.AssetLibrary; }
    void SetAssetLibrary(const AssetLibrary& assetLibrary) { _desc.AssetLibrary = assetLibrary; }

    Camera * GetCamera() const { return _desc.Camera; }

    const Timestep& GetTimestep() const;

private:
    void BindBaseCallbackAndLayerStack();

private:
    ApplicationDescription _desc;

    Timestep _timestep;
};
}

#endif