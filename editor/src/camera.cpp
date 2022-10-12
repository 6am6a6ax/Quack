#include "quack-editor/camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/matrix.hpp"
#include "quack/core/event.h"
#include "quack/core/event_type.h"
#include "quack/core/key_event.h"
#include "quack/core/mouse_event.h"
#include "quack/math/math.h"
#include "quack/render/camera.h"
#include <cmath>
#include <math.h>

Quack::Editor::CameraEditor::CameraEditor() : Quack::Camera(),
    _position({0.0f, 0.0f, 2.0f}),
    _target({0.0f, 0.0f, 0.0f}),
    _up({0.0f, 1.0f, 0.0f})
{
    _forward = glm::normalize(_position - _target);
    _right = glm::normalize(glm::cross(_up, _forward));
    _up = glm::cross(_forward, _right);
}

void Quack::Editor::CameraEditor::OnEvent(Event& e) {
    switch (e.GetType()) {
        case Quack::EventType::MouseButtonPressedEvent: 
            OnMouseButtonPressed(dynamic_cast<MouseButtonPressedEvent&>(e));
            break;
        case Quack::EventType::KeyPressedEvent: 
            OnKeyPressed(dynamic_cast<KeyPressedEvent&>(e));
            break;
    }
}

void Quack::Editor::CameraEditor::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
}

void Quack::Editor::CameraEditor::OnKeyPressed(KeyPressedEvent& e) {
}


void Quack::Editor::CameraEditor::OnUpdate(Timestep ts) {

    Mat4f proj = glm::perspective(90.0f, (float)1280 / (float)720, 1.0f, 100.0f);
    // Mat4f view = glm::lookAt(Vector3f(-1.0f, 1.0f, 1.0f), 
    //                          _target, 
    //                          Vector3f(0.0f, 1.0f, 0.0f));

    float radius = 2.5f;

    float x = sinf(Quack::Application::GetInstance().GetWindow()->GetTime()) * radius;
    float z = cosf(Quack::Application::GetInstance().GetWindow()->GetTime()) * radius;

    Mat4f view = glm::lookAt(
        Vector3f(x, 0.0f, z),
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(0.0f, 1.0f, 0.0f)
    );

    _viewProj = proj * view;
}

const Quack::Editor::CameraEditor::Viewport& Quack::Editor::CameraEditor::GetViewport() const {}

const Quack::Mat4f& Quack::Editor::CameraEditor::GetView() const {
    return _view;
}

const Quack::Mat4f& Quack::Editor::CameraEditor::GetViewProj() const {
    return _viewProj;
}

void Quack::Editor::CameraEditor::SetViewport(uint32_t width, uint32_t height) {}

const Quack::Vector3f& Quack::Editor::CameraEditor::GetPosition() const {
    return _position;
}

const Quack::Vector3f& Quack::Editor::CameraEditor::GetTarget() const {
    return _target;
}

const Quack::Vector3f& Quack::Editor::CameraEditor::GetUp() const {
    return _up;
}

const Quack::Vector3f& Quack::Editor::CameraEditor::GetRight() const {
    return _right;
}

const Quack::Vector3f& Quack::Editor::CameraEditor::GetForward() const {
    return _forward;
}

