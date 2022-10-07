#ifndef QUACK_MATH_H
#define QUACK_MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Quack {
    using Vector2f = glm::vec2;
    using Vector3f = glm::vec3;
    using Vector4f = glm::vec4;

    using Vector2i = glm::ivec2;
    using Vector3i = glm::ivec3;
    using Vector4i = glm::ivec4;

    using Vector2u = glm::uvec2;
    using Vector3u = glm::uvec3;
    using Vector4u = glm::uvec4;

    using Mat2f = glm::mat2;
    using Mat3f = glm::mat3;
    using Mat4f = glm::mat4;

    using Mat2x3f = glm::mat2x3;
    using Mat3x2f = glm::mat3x2;

    using Mat2x4f = glm::mat2x4;
    using Mat4x2f = glm::mat4x2;

    using Mat3x4f = glm::mat3x4;
    using Mat4x3f = glm::mat4x3;
}

#endif
