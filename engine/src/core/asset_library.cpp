#include "quack/quack.h"

Quack::AssetLibrary::AssetLibrary() : m_Root(std::filesystem::path{}) {
    SetupCurrentPath();
}

// TODO: boost::filepath?
void Quack::AssetLibrary::SetupCurrentPath() {
    char szPath[256];
    ssize_t count = readlink("proc/self/exe", szPath, 256);
    if (count < 0 || count >= 256) {
        throw std::exception();
    }
    szPath[count] = '\0';
    m_Root = std::filesystem::path{ szPath }.parent_path() / "";
}

std::shared_ptr<Quack::GPUShader> Quack::AssetLibrary::LoadShader(const std::string& filename) const {
    return Quack::Application::GetInstance().GetDevice()->CreateShader(ParseShaderFile(filename));
}

std::shared_ptr<Quack::GPUTexture> Quack::AssetLibrary::LoadTexture(const std::string& filename) const {
    GPUTextureDescription desc;
    desc.Path = m_Root + "textures/" + filename;

    return Application::GetInstance().GetDevice()->CreateTexture(desc);
}

std::shared_ptr<Quack::Model> Quack::AssetLibrary::LoadModel(const std::string &filename) const {
    return std::make_shared<Model>(m_Root + "models/" + filename);
}

Quack::GPUShaderDescription Quack::AssetLibrary::ParseShaderFile(const std::string& filename) const {
    GPUShaderProgramDescription vertexShaderProgramDesc;
    GPUShaderProgramDescription fragmentShaderProgramDesc;

    std::string filepath = m_Root + "shaders/" + filename;

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

    return { Application::GetInstance().GetDevice()->CreateShaderProgram(vertexShaderProgramDesc),
             Application::GetInstance().GetDevice()->CreateShaderProgram(fragmentShaderProgramDesc) };
}