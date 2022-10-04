#ifndef MODEL_LOADER_LAYER_TEST_H
#define MODEL_LOADER_LAYER_TEST_H

#include <quack/quack.h>

namespace ModelLoader {
class LayerTest final : public Quack::Layer {
public:
    explicit LayerTest(const std::string & name);
    ~LayerTest() override {}

public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Quack::Event &) override;

private:
    Quack::Model _model;
};
}

#endif