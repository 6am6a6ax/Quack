#include "quack/quack.h"

Quack::Light::Light(const Quack::Vector3f& color, float intensity) 
    : _color(color), 
      _intensity(intensity) {}

Quack::DirectionalLight::DirectionalLight(const Quack::Mat4f& world,
                                          const Quack::Vector3f& direction,
                                          const Quack::Vector3f& color,
                                          float intensity)
    : Quack::Light(color, intensity),
      _world(direction)
{
    Compute(world);
}

const Quack::Vector3f& Quack::DirectionalLight::GetColor() const {
    return _color;
}

const float Quack::DirectionalLight::GetIntensity() const {
    return _intensity;
}

const Quack::Vector3f& Quack::DirectionalLight::GetLocal() const {
    return _local;
}

const Quack::Vector3f& Quack::DirectionalLight::GetWorld() const {
    return _world;
}

void Quack::DirectionalLight::SetColor(const Vector3f& color) {
    _color = color;
}

void Quack::DirectionalLight::SetIntensity(float intensity) {
    _intensity = intensity;
}

void Quack::DirectionalLight::Compute(const Quack::Mat4f& world) {
    _local = glm::normalize(glm::transpose(Mat3f(world)) * _world);
}