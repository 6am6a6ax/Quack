#include "quack/quack.h"
#include <memory>

std::shared_ptr<Quack::GPUShader> Quack::AssetLibrary::LoadShader(const std::string& filename) const {
    return Quack::Application::GetInstance().GetDevice()->CreateShader(ParseShaderFile(filename));
}

std::shared_ptr<Quack::GPUTexture> Quack::AssetLibrary::LoadTexture(const std::string& filename) const {
    GPUTextureDescription desc;
    desc.Path = _root + "textures/" + filename;

    return Application::GetInstance().GetDevice()->CreateTexture(desc);
}

std::shared_ptr<Quack::Model> Quack::AssetLibrary::LoadModel(const std::string &filename) const {
    return std::make_shared<Model>(_root + "models/" + filename);
}

Quack::GPUShaderDescription Quack::AssetLibrary::ParseShaderFile(const std::string& filename) const {
    GPUShaderProgramDescription vertexShaderProgramDesc;
    GPUShaderProgramDescription fragmentShaderProgramDesc;

    std::string filepath = _root + "shaders/" + filename;

    std::ifstream file(filepath);
    if (file.fail()) {
        std::cout << "File (" << filepath << ") not found!\n";
    }

    std::string line;
    std::string type;
    while (std::getline(file, line))
    {
        size_t typeTokenPos = line.find("#type");
        if (typeTokenPos != std::string::npos) {
            size_t eol = line.find_first_of("\r\n", typeTokenPos);
            size_t begin = typeTokenPos + strlen("#type") + 1;
            type = line.substr(begin, eol - begin);
            continue;
        }
        if (type == "vertex") {
            vertexShaderProgramDesc.Source += line + "\n";
        }
        else if (type == "fragment") { 
            fragmentShaderProgramDesc.Source += line + "\n";
        }
    }

    file.close();

    vertexShaderProgramDesc.Name = filename;
    vertexShaderProgramDesc.Type = ShaderProgramType::Vertex;
    fragmentShaderProgramDesc.Name = filename;
    fragmentShaderProgramDesc.Type = ShaderProgramType::Fragment;

    GPUShaderDescription result;
    result.VertexShader = Application::GetInstance().GetDevice()->CreateShaderProgram(vertexShaderProgramDesc);
    result.FragmentShader = Application::GetInstance().GetDevice()->CreateShaderProgram(fragmentShaderProgramDesc);

    return result;
}