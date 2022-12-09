#ifndef QUACK_ASSET_LIBRARY_H
#define QUACK_ASSET_LIBRARY_H

#include <memory>
#include <string>

#include "quack/graphics/gpu_shader.h"
#include "quack/graphics/gpu_texture.h"
#include "quack/scene/model.h"

#include "unistd.h"


namespace Quack {
class AssetLibrary {
public:
    AssetLibrary();
    ~AssetLibrary() = default;

    std::shared_ptr<GPUShader> LoadShader(const std::string& filename) const;
    std::shared_ptr<GPUTexture> LoadTexture(const std::string& filename) const;
    std::shared_ptr<Model> LoadModel(const std::string& filename) const;

private:
    GPUShaderDescription ParseShaderFile(const std::string & filename) const;

private:
    void SetupCurrentPath();

private:
    std::filesystem::path m_Root;
};
}

#endif