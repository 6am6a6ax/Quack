#ifndef QUACK_CAMERA_H
#define QUACK_CAMERA_H

#include "quack/math/math.h"
#include "quack/core/timestep.h"
#include <cstdint>

namespace Quack {
class Camera {
public:
    virtual ~Camera() = default;

public:
    virtual void OnEvent(Event&) = 0;
    virtual void OnUpdate(Timestep) = 0;

public:
    // virtual bool IsActive() const = 0;

public:
    // virtual const Vector3f& GetPosition() const = 0;

public:
    // virtual Vector3f& GetUp() const = 0;
    // virtual Vector3f& GetRight() const = 0;
    // virtual Vector3f& GetForward() const = 0;

public:
    virtual const Mat4f& GetView() const = 0;
    // virtual const Mat4f& GetProj() const = 0;
    virtual const Mat4f& GetViewProj() const = 0;

public:
    // virtual void SetActive(bool) = 0;
    
    // virtual void SetViewport(uint32_t width, uint32_t height) = 0;
};
}

#endif