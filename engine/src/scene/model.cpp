#include "assimp/material.h"
#include "assimp/types.h"
#include "quack/core/application.h"
#include "quack/graphics/gpu_texture_description.h"
#include "quack/quack.h"
#include <cstdint>
#include <memory>

void Quack::Model::Load(const std::string & filepath) {
    Assimp::Importer importer;
    const aiScene * scene = importer.ReadFile(filepath,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "An error was found while loading model with Assimp: " << importer.GetErrorString() << std::endl;
    }

    uint32_t numIndex = { 0 };
    uint32_t numVertex = { 0 };

    _submeshes.reserve(scene->mNumMeshes);
    for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh * mesh = scene->mMeshes[i];

        Submesh & submesh = _submeshes.emplace_back();
        submesh.Name =mesh->mName.C_Str();
        submesh.BaseIndex = numIndex;
        submesh.BaseVertex = numVertex;
        submesh.NumIndex = mesh->mNumFaces * 3;
        submesh.NumVertex = mesh->mNumVertices;
        submesh.MaterialIndex = mesh->mMaterialIndex;

        numIndex += submesh.NumIndex;
        numVertex += submesh.NumVertex;
    }

    _indices.reserve(numIndex);
    _vertices.reserve(numVertex);

    for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh * mesh = scene->mMeshes[i];

        for (uint32_t j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;
            vertex.Position = { mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z };
            vertex.Normal = { mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z };

            vertex.TexCoord = mesh->HasTextureCoords(0)
                ? Vector2f({ mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y })
                : Vector2f({ 0.0f, 0.0f });

            std::cout << "TexCoord [" << j << "]: x=" << vertex.TexCoord.x << "; y=" << vertex.TexCoord.y << "\n";

            _vertices.push_back(vertex);
        }

        for (uint32_t j = 0; j < mesh->mNumFaces; j++) {
            const aiFace & face = mesh->mFaces[j];

            _indices.push_back(static_cast<uint32_t>(face.mIndices[0]));
            _indices.push_back(static_cast<uint32_t>(face.mIndices[1]));
            _indices.push_back(static_cast<uint32_t>(face.mIndices[2]));
        }
    }

    for (uint32_t i = 0; i < scene->mNumMaterials; i++) {
        const aiMaterial * material = scene->mMaterials[i];

        // std::cout << "Diffuse textures count: " << material->GetTextureCount(aiTextureType_DIFFUSE) << "\n";
        // std::cout << "Specular textures count: " << material->GetTextureCount(aiTextureType_SPECULAR) << "\n";
        // std::cout << "Ambient textures count: " << material->GetTextureCount(aiTextureType_AMBIENT) << "\n";
        // std::cout << "Emissive textures count: " << material->GetTextureCount(aiTextureType_EMISSIVE) << "\n";
        // std::cout << "Height textures count: " << material->GetTextureCount(aiTextureType_HEIGHT) << "\n";
        // std::cout << "Normals textures count: " << material->GetTextureCount(aiTextureType_NORMALS) << "\n";
        // std::cout << "Shininess textures count: " << material->GetTextureCount(aiTextureType_SHININESS) << "\n";
        // std::cout << "Opacity textures count: " << material->GetTextureCount(aiTextureType_OPACITY) << "\n";
        // std::cout << "Displacement textures count: " << material->GetTextureCount(aiTextureType_DISPLACEMENT) << "\n";
        // std::cout << "Lightmap textures count: " << material->GetTextureCount(aiTextureType_LIGHTMAP) << "\n";
        // std::cout << "Reflection textures count: " << material->GetTextureCount(aiTextureType_REFLECTION) << "\n";

        GPUTextureDescription desc = {};
        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                std::string p(path.data);

                size_t last = p.find_last_of("\\");
                size_t tail = p.find("\\n");

                p = p.substr(++last, p.size() - last);

                std::string fullPath = p;

                desc.Path = R"(/home/bujhm/dev/cpp/cg/quack/engine/assets/models/building/texteur/)" + p;

                std::cout << "Model texture path: " << desc.Path << "\n";

            }
        }
        _textures.push_back(Application::GetInstance().GetDevice()->CreateTexture(desc));
    }

    Quack::GPUBuffer::Layout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float3, "a_Normal" },
        { ShaderDataType::Float2, "a_TexCoord" }
    };

    Quack::GPUBuffer::Description vboDesc;
    vboDesc.LayoutDesc = layout;
    vboDesc.Data = _vertices.data();
    vboDesc.Size = _vertices.size() * sizeof(_vertices[0]);
    vboDesc.Type = BufferType::Vertex;
    _vbo = Quack::Application::GetInstance().GetDevice()->CreateBuffer(vboDesc);

    _vao = Quack::Application::GetInstance().GetDevice()->CreateVertexArray();
    _vao->AddBuffer(_vbo);

    Quack::GPUBuffer::Description iboDesc;
    iboDesc.Data = _indices.data();
    iboDesc.Size = _indices.size() * sizeof(_indices[0]);
    iboDesc.Type = BufferType::Index;
    _ibo  = Quack::Application::GetInstance().GetDevice()->CreateBuffer(iboDesc);

    _shader = Quack::Application::GetInstance().GetAssetLibrary().LoadShader("model.glsl");
}