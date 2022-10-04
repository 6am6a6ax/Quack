#include "quack-model-loader/layers/layer_test.h"

using namespace Quack;

ModelLoader::LayerTest::LayerTest(const std::string & name) : Quack::Layer(name), _model(Quack::Model()) {}

void ModelLoader::LayerTest::OnAttach() {
    _model.Load("./building.fbx");
}

void ModelLoader::LayerTest::OnDetach() {}

void ModelLoader::LayerTest::OnUpdate() {}

void ModelLoader::LayerTest::OnEvent(Quack::Event & e) {}