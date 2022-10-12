#ifndef QUACK_LIGHT_H
#define QUACK_LIGHT_H

#include "quack/math/math.h"

namespace Quack {
class Light {
public:
    Light(const Vector3f& color = { 1.0f, 1.0f, 1.0f }, float intensity = 1.0f);
    virtual ~Light() = default;
public:
    Vector3f _color;
    float _intensity;
};

class DirectionalLight final : public Light {
public:
    DirectionalLight(const Mat4f& world,
                     const Vector3f& direction = { 0.0f, 0.0f, 0.0f },
                     const Vector3f& color = { 1.0f, 1.0f, 1.0f },
                     float intencity = 1.0f);
    ~DirectionalLight() override = default;

public:
    const Vector3f& GetColor() const;
    const float GetIntensity() const;

    const Vector3f& GetLocal() const;
    const Vector3f& GetWorld() const;

public:
    void SetColor(const Vector3f& color);
    void SetIntensity(float intensity);

private:
    void Compute(const Mat4f& world);

public:
    Vector3f _local;
    Vector3f _world;
};
}

#endif