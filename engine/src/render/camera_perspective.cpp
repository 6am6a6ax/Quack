#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "quack/math/math.h"
#include <quack/quack.h>

void Quack::CameraPerspective::OnEvent(Event& event) {}

void Quack::CameraPerspective::OnUpdate(Timestep timestep) {
    _view = glm::lookAt(_position, { 0.f, 0.f, 0.f }, _up); 
    _proj = glm::perspective(60.f, 1280.f / 720.f, 1.f, 100.f);
    _viewProj = _view * _proj;
}

const Quack::Mat4f& Quack::CameraPerspective::GetView() const {
    return _view;
}

const Quack::Mat4f& Quack::CameraPerspective::GetProj() const {
    return _proj;
}

const Quack::Mat4f& Quack::CameraPerspective::GetViewProj() const {
    return _viewProj;
}