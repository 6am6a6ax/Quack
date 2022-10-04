#ifndef QUACK_APPLICATION_H
#define QUACK_APPLICATION_H

#include "quack/core/event.h"
#include "quack/core/window.h"

#include "quack/graphics/gpu_device.h"

#include "quack/scene/scene.h"

namespace Quack {
struct ApplicationDescription {
    Quack::Window * Window;
    Quack::GPUDevice * GPUDevice;
    Quack::LayerStack LayerStack;

    Quack::Scene * Scene;
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

private:
    void BindBaseCallbackAndLayerStack();

private:
    ApplicationDescription _desc;
};
}

#endif