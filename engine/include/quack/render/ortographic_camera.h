#ifndef QUACK_ORTOGRAPHIC_CAMERA_H
#define QUACK_ORTOGRAPHIC_CAMERA_H

#include "quack/math/math.h"

namespace Quack {
class OrtographicCamera {
public:
    OrtographicCamera(float left, float right, float bottom, float top);

public:
    const Vector3f & GetPosition() const;
    void SetPosition(const Vector3f &);

    float GetRotation() const;
    void SetRotation(float);

    const Mat4f & GetView() const;
    void SetView(const Mat4f &);

    const Mat4f & GetProjection() const;
    void SetProjection(const Mat4f &);

    const Mat4f & GetViewProj() const;
    void SetViewProj(const Mat4f &);

private:
    void RecalculateViewMatrix();

private:
    Mat4f _view;
    Mat4f _projection;
    Mat4f _viewProj;

    Vector3f _position;

    float _rot;
};
}

#endif
