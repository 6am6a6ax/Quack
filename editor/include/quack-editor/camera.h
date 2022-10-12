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

    void OnMouseMoved(MouseMovedEvent&);
    void OnMouseButtonPressed(MouseButtonPressedEvent&);
    void OnMouseButtonReleased(MouseButtonReleasedEvent&);

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
    Vector3f _position = {0.0f, 0.0f, 0.0f};
    Vector3f _target = {0.0f, 0.0f, 0.0f};

    float _yaw = 0;
    float _pitch = 0;

    bool _isActive = false;

    Vector3f _up = {0.0f, 1.0f, 0.0f};
    Vector3f _right = {1.0f, 0.0f, 0.0f};
    Vector3f _forward = {0.0f, 0.0f, 1.0f};

    Mat4f _view = Mat4f(1.0f);
    Mat4f _proj = Mat4f(1.0f);
    Mat4f _viewProj = Mat4f(1.0f);

    Viewport _viewport;
};
}

#endif
