#ifndef QUACK_COMPONENTS_H
#define QUACK_COMPONENTS_H

#include <string>

#include "quack/math/math.h"

namespace Quack {
struct TagComponent {
    std::string Tag;
    TagComponent() = default;
    TagComponent(const std::string & tag = "Unnamed") : Tag(tag) {}
};

struct TransformComponent {
    Vector3f Translation = {0.0f, 0.0f, 0.0f};
    Vector3f Rotation = {0.0f, 0.0f, 0.0f};
    Vector3f Scale = {1.0f, 1.0f, 1.0f};
    TransformComponent() = default;
    TransformComponent(const Vector3f & translation) : Translation(translation) {}
    Mat4f  GetTransform() const {
        Mat4f rotation = glm::toMat4(glm::quat(rotation));

        return glm::translate(glm::mat4(1.0f), Translation)
            * rotation
            * glm::scale(glm::mat4(1.0f), Scale);
    }
};
struct SpriteRendererComponent {
    Vector4f Color = {1.0f, 1.0f, 1.0f, 1.0f};
    SpriteRendererComponent() = default;
    SpriteRendererComponent(const Vector4f & color) : Color(color) {}
};

//struct CameraComponent {
//    SceneCamera Camera;
//    bool Primary = false;
//    bool FixedAspectRatio = false;
//};
}

#endif
