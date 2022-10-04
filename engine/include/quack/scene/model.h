#ifndef QUACK_MODEL_H
#define QUACK_MODEL_H

#include <string>

namespace Quack {
class Model {
public:
    void Load(const std::string & filepath);

    std::vector<Vertex> GetVertices() const { return _vertices; }
    std::vector<uint32_t> GetIndices() const { return _indices; }
    std::vector<Submesh> GetSubmesher() const { return _submeshes; }

private:
    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;
    std::vector<Submesh> _submeshes;
};
}

#endif