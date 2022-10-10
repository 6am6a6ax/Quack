#ifndef QUACK_ASSET_LIBRARY_H
#define QUACK_ASSET_LIBRARY_H

#include <memory>
#include <string>

#include "quack/graphics/gpu_shader.h"
#include "quack/graphics/gpu_texture.h"

namespace Quack {
class AssetLibrary {
public:
    AssetLibrary(const std::string& root = "assets/") : _root(root) {}
    ~AssetLibrary() = default;

    std::shared_ptr<GPUShader> LoadShader(const std::string& filename) const;
    std::shared_ptr<GPUTexture> LoadTexture(const std::string& filename) const;

private:
    GPUShaderDescription ParseShaderFile(const std::string & filename) const;

private:
    std::string _root;
};
}

#endif