#include "quack/quack.h"

Quack::OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top)
    : _rot(.0f), _projection(glm::ortho(left, right, bottom, top)), _view(1.f), _position(0.0f, 0.0f, 0.0f)
{
    _viewProj = _projection * _view;
    RecalculateViewMatrix();
}

const Quack::Vector3f &Quack::OrtographicCamera::GetPosition() const {
    return _position;
}

void Quack::OrtographicCamera::SetPosition(const Quack::Vector3f & position) {
    _position = position;
    RecalculateViewMatrix();
}

float Quack::OrtographicCamera::GetRotation() const {
    return _rot;
}

void Quack::OrtographicCamera::SetRotation(float rot) {
    _rot = rot;
    RecalculateViewMatrix();
}

const Quack::Mat4f & Quack::OrtographicCamera::GetView() const {
    return _view;
}

void Quack::OrtographicCamera::SetView(const Quack::Mat4f & view) {
    _view = view;
}

const Quack::Mat4f & Quack::OrtographicCamera::GetProjection() const {
    return _projection;
}

void Quack::OrtographicCamera::SetProjection(const Quack::Mat4f & projection) {
    _projection = projection;
}

const Quack::Mat4f& Quack::OrtographicCamera::GetViewProj() const {
    return _viewProj;
}

void Quack::OrtographicCamera::SetViewProj(const Quack::Mat4f & viewProj) {
    _viewProj = viewProj;
}

void Quack::OrtographicCamera::RecalculateViewMatrix() {
    Mat4f transform = glm::translate(Mat4f(1.0f), _position) *
            glm::rotate(glm::mat4(1.0f), _rot, Vector3f (.0f, .0f, 1.f));

    _view = glm::inverse(transform);
    _viewProj = _projection * _view;
}