#ifndef QUACK_RENDERER_H
#define QUACK_RENDERER_H

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_shader.h"
#include <memory>
#include <quack/math/math.h>
#include <quack/graphics/gpu_pipeline.h>
#include <quack/graphics/gpu_uniform_buffer.h>
#include <quack/render/light.h>

namespace Quack {
class Renderer {
public:
    static void Begin();
    static void End();

public:
    static void RenderQuad();
    static void RenderGrid();
    static void RenderCube();
    static void RenderModel(const std::shared_ptr<Model>& model, const DirectionalLight& light, const Mat4f& transform);
};
}

#endif
