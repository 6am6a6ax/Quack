#ifndef EDITOR_CAMERA_H
#define EDITOR_CAMERA_H

#include "quack/core/key_event.h"
#include "quack/math/math.h"
#include <cstdint>
#include <quack/render/camera.h>

namespace Quack::Editor {
class CameraEditor final : public Camera {
public:
    struct Viewport {
        uint32_t Width;
        uint32_t Height;
    };
public:
    CameraEditor();
    ~CameraEditor() override = default;

public:
    void OnEvent(Event&);
    void OnUpdate(Timestep);

public:
    void OnKeyPressed(KeyPressedEvent&);
    void OnMouseButtonPressed(MouseButtonPressedEvent&);

public:
    const Viewport& GetViewport() const;

    const Vector3f& GetTarget() const;
    const Vector3f& GetPosition() const;

    const Vector3f& GetUp() const;
    const Vector3f& GetRight() const;
    const Vector3f& GetForward() const;

    const Mat4f& GetView() const;
    const Mat4f& GetViewProj() const;

public:
    void SetViewport(uint32_t width, uint32_t height);

private:
    Vector3f _position;
    Vector3f _target;

    Vector3f _up;
    Vector3f _right;
    Vector3f _forward;

    Mat4f _view;
    Mat4f _proj;
    Mat4f _viewProj;

    Viewport _viewport;
};
}

#endif
