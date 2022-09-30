#ifndef QUACK_MATH_H
#define QUACK_MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Quack {
    using Vector1f = glm::vec1;
    using Vector2f = glm::vec2;
    using Vector3f = glm::vec3;
    using Vector4f = glm::vec4;

    using Mat3f = glm::mat3;
    using Mat4f = glm::mat4;
}

#endif
