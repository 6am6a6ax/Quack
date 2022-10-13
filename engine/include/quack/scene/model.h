#ifndef QUACK_MODEL_H
#define QUACK_MODEL_H

#include <memory>
#include <string>
#include <vector>

#include "quack/math/math.h"
#include "quack/scene/mesh.h"

#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_vertex_array.h"
#include "quack/graphics/gpu_shader.h"


namespace Quack {
class Model {
public:
    Model(const std::string& filepath) {
        Load(filepath);
    }

    void Load(const std::string & filepath);

    std::vector<Vertex> GetVertices() const { return _vertices; }
    std::vector<uint32_t> GetIndices() const { return _indices; }
    std::vector<Submesh> GetSubmeshes() const { return _submeshes; }

    std::shared_ptr<GPUBuffer> GetVBO() const { return _vbo; }
    std::shared_ptr<GPUBuffer> GetIBO() const { return _ibo; }
    std::shared_ptr<GPUVertexArray> GetVAO() const { return _vao; }

    std::shared_ptr<GPUShader> GetShader() const { return _shader; }

    const std::vector<std::shared_ptr<GPUTexture>>& GetTextures() const { return _textures; }

private:
    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;

    std::vector<Submesh> _submeshes;

    std::vector<std::shared_ptr<GPUTexture>> _textures;

    std::shared_ptr<GPUBuffer> _vbo;
    std::shared_ptr<GPUBuffer> _ibo;

    std::shared_ptr<GPUVertexArray> _vao;

    std::shared_ptr<GPUShader> _shader;
};
}

#endif