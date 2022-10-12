#ifndef QUACK_LAYER_QUAD_H
#define QUACK_LAYER_QUAD_H

#include "quack/core/layer.h"

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_vertex_array.h"
#include "quack/graphics/gpu_device.h"

#include "quack/scene/scene.h"
#include "quack/render/light.h"
#include "quack/scene/model.h"
#include "quack/scene/entity.h"
#include "quack/render/ortographic_camera.h"
#include "quack/scene/components.h"

#include "quack/core/application.h"

#include "quack-editor/scene_editor.h"
#include <memory>

namespace Quack::Editor {
class LayerQuad final : public Layer {
public:
    explicit LayerQuad(const std::string& name);
    ~LayerQuad() override;

public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event&) override;
private:
    std::shared_ptr<GPUFramebuffer> _framebuffer;
    std::shared_ptr<Model> _model;
    DirectionalLight _light;
};
}

#endif
