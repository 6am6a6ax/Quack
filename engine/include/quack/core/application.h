#ifndef QUACK_APPLICATION_H
#define QUACK_APPLICATION_H

#include <memory>

#include "event.h"
#include "application_description.h"

#include "quack/core/timestep.h"

namespace Quack {
class Application {
    Application() = default;

public:
    static Application & GetInstance();
    virtual ~Application() = default;

public:
    Application(const Application &) = delete;
    Application & operator=(const Application &) = delete;

public:
    void Init(const WindowDescription &);
    void Run();

public:
    void OnEvent(Event &);

public:
    ApplicationDescription & GetDescription();
    void SetDescription(ApplicationDescription &);

private:
    ApplicationDescription _description;

    float _lastFrameTime;
};
}

#endif