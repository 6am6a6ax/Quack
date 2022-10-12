#include "quack/quack.h"
#include <cstdint>

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
        submesh.MaterialIndex =mesh->mMaterialIndex;

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

            std::cout << "Normal [" << j << "]: x=" << vertex.Normal.x << "; y=" << vertex.Normal.y << "; z="
                << vertex.Normal.z << ";\n";

            // vertex.TexCoord = mesh->HasTextureCoords(0)
            //     ? Vector2f({ mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y })
            //     : Vector2f({ 0.0f, 0.0f });

            _vertices.push_back(vertex);

            // _vertices.push_back({mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z});
        }

        for (uint32_t j = 0; j < mesh->mNumFaces; j++) {
            const aiFace & face = mesh->mFaces[j];

            _indices.push_back(static_cast<uint32_t>(face.mIndices[0]));
            _indices.push_back(static_cast<uint32_t>(face.mIndices[1]));
            _indices.push_back(static_cast<uint32_t>(face.mIndices[2]));
        }
    }

    Quack::GPUBuffer::Layout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float3, "a_Normal" }
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