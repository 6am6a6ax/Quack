#ifndef QUACK_RENDERER_H
#define QUACK_RENDERER_H

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_shader.h"
#include <quack/math/math.h>
#include <quack/graphics/gpu_pipeline.h>
#include <quack/graphics/gpu_uniform_buffer.h>

namespace Quack {
class Renderer {
public:
    static void Begin();
    static void End();

public:
    static void RenderQuad();
};
}

#endif
