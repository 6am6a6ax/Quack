#ifndef QUACK_LAYER_QUAD_H
#define QUACK_LAYER_QUAD_H

#include "quack/core/layer.h"

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_vertex_array.h"
#include "quack/graphics/gpu_device.h"

#include "quack/scene/scene.h"
#include "quack/scene/entity.h"
#include "quack/render/ortographic_camera.h"
#include "quack/scene/components.h"

#include "quack/core/application.h"

#include "quack-editor/scene_editor.h"

namespace Quack {
class LayerQuad final : public Layer {
public:
    explicit LayerQuad(const std::string & name, SceneEditor * scene);
    ~LayerQuad() override;

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

    Vector4f _color = {0.0, 1.0, 0.0, 1.0};
    Entity _quad;
    Entity _quad2;

    SceneEditor * _scene;
};
}

#endif
