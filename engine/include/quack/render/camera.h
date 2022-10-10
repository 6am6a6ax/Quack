#ifndef QUACK_CAMERA_H
#define QUACK_CAMERA_H

#include "quack/math/math.h"
#include "quack/core/timestep.h"

namespace Quack {
class ICamera {
public:
    virtual ~ICamera() = default;

public:
    virtual void OnEvent(Event&) = 0;
    virtual void OnUpdate(Timestep) = 0;

public:
    virtual bool IsActive() const = 0;

public:
    virtual const Mat4f& GetView() const = 0;
    virtual const Mat4f& GetViewProj() const = 0;

public:
    virtual void SetActive(bool) = 0;
};
}

#endif