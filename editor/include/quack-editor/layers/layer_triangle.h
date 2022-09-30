#ifndef QUACK_LAYER_TRIANGLE_H
#define QUACK_LAYER_TRIANGLE_H

#include "quack/core/layer.h"

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_vertex_array.h"
#include "quack/graphics/gpu_device.h"

#include "quack/render/ortographic_camera.h"

namespace Quack {
class LayerTriangle final : public Layer {
public:
    explicit LayerTriangle(const std::string & name);
    ~LayerTriangle() override;

public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event &) override;
private:
    GPUBuffer * _vbo;
    GPUBuffer * _ebo;
    GPUVertexArray * _vao;
    GPUTexture * _texture;
    GPUShader * _shader;
    GPUFramebuffer * _framebuffer;

    OrtographicCamera _camera;
};
}

#endif
