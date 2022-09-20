#ifndef QUACK_GPU_CONTEXT_OPENGL_H
#define QUACK_GPU_CONTEXT_OPENGL_H

#include <GLFW/glfw3.h>
#include "quack/graphics/gpu_context.h"

namespace Quack {
class GPUContextOpenGL final : public GPUContext {
public:
    explicit GPUContextOpenGL(GLFWwindow *);

public:
    void Init() override;
    void SwapBuffers() override;

private:
    GLFWwindow * _handle;
};
}

#endif
