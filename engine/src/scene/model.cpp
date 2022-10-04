#include "quack/quack.h"

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
        aiMesh * mesh = scene->mMeshes[i];

        Submesh & submesh = _submeshes.emplace_back();
        submesh.Name = mesh->mName.C_Str();
        submesh.BaseIndex = numIndex;
        submesh.BaseVertex = numVertex;
        submesh.NumIndex = mesh->mNumFaces * 3;
        submesh.NumVertex = mesh->mNumVertices;
        submesh.MaterialIndex = mesh->mMaterialIndex;

        numIndex += submesh.NumIndex;
        numVertex += submesh.BaseVertex;

        delete mesh;
    }

    _indices.reserve(numIndex);
    _vertices.reserve(numVertex);

    for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh * mesh = scene->mMeshes[i];

        for (uint32_t j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;
            vertex.Position = { mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z };
            vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
            vertex.TexCoord = mesh->HasTextureCoords(0)
                ? Vector2f({ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y })
                : Vector2f({ 0.0f, 0.0f });

            _vertices.push_back(vertex);
        }

        for (uint32_t j = 0; j < mesh->mNumFaces; j++) {
            const aiFace & face = mesh->mFaces[i];

            _indices.push_back({face.mIndices[0]});
            _indices.push_back({face.mIndices[1]});
            _indices.push_back({face.mIndices[2]});
        }

        delete mesh;
    }

    delete scene;
}