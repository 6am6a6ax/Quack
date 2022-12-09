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
    std::shared_ptr<Quack::LayerStack> LayerStack;
    std::shared_ptr<Quack::AssetLibrary> AssetLibrary;
    std::shared_ptr<Quack::Scene> Scene;
    std::shared_ptr<Quack::Camera> Camera;
    std::shared_ptr<Quack::GPUFramebuffer> GPUFramebuffer;
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
    const ApplicationDescription & GetDescription() const;

public:
    float GetTime() const;
    const Timestep& GetTimestep() const;

public:
    std::shared_ptr<Scene> GetScene() const;
    std::shared_ptr<Window> GetWindow() const;
    std::shared_ptr<Camera> GetCamera() const;
    std::shared_ptr<GPUDevice> GetDevice() const;
    std::shared_ptr<LayerStack> GetLayerStack() const;
    std::shared_ptr<AssetLibrary> GetAssetLibrary() const;

private:
    void BindBaseCallbackAndLayerStack();

private:
    ApplicationDescription m_Description;
    Timestep m_Timestep;
};
}

#endif