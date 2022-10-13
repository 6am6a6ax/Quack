#ifndef QUACK_MESH_H
#define QUACK_MESH_H

#include <cstdint>
#include <string>
#include <vector>

#include "quack/math/math.h"

namespace Quack {
struct Vertex {
    Vector3f Position;
    Vector3f Normal;
    Vector2f TexCoord;
};

struct Texture {
    uint32_t Id;
    std::string Type;
};

struct Submesh {
    const char * Name;

    uint32_t NumIndex;
    uint32_t NumVertex;

    uint32_t BaseIndex;
    uint32_t BaseVertex;

    uint32_t MaterialIndex;
};

class Mesh {
private:
    std::vector<Submesh> _submeshes;

    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;
    std::vector<Texture> _textures;
};
}

#endif
