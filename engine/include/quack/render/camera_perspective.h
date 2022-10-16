#ifndef QUACK_CAMERA_PERSPECTIVE_H
#define QUACK_CAMERA_PERSPECTIVE_H

#include "quack/core/event.h"
#include "quack/core/timestep.h"

#include "quack/math/math.h"

#include "quack/render/camera.h"

namespace Quack {
class CameraPerspective final : public Camera {
public:
    CameraPerspective() = default;
    ~CameraPerspective() override = default;

public:
    void OnUpdate(Timestep) override;
    void OnEvent(Event&) override;

public:
    const Mat4f& GetView() const override;
    const Mat4f& GetProj() const;
    const Mat4f& GetViewProj() const override;

private:
    Vector3f _position;

    Vector3f _up;
    Vector3f _right;
    Vector3f _forward;

    Mat4f _view;
    Mat4f _proj;
    Mat4f _viewProj;
};
}

#endif