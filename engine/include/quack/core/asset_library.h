#ifndef QUACK_ASSET_LIBRARY_H
#define QUACK_ASSET_LIBRARY_H

#include "quack/core/application.h"
#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_device.h"
#include "quack/graphics/gpu_shader.h"
#include "quack/graphics/gpu_shader_program.h"
#include <cstddef>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>

namespace Quack {
class AssetLibrary {
public:
    AssetLibrary(const std::string & root = "./assets/") : _root(root) {}
    ~AssetLibrary() = default;

    GPUShader * LoadShader(const std::string & filename) {
        return Application::GetInstance().GetDevice()->CreateShader(ParseShaderFile(filename));
    }

    void LoadModel() const {
        
    }

    GPUTexture * LoadTexture(const std::string & filename) const {
        GPUTextureDescription desc;
        desc.Path = _root + "textures/" + filename;

        return Application::GetInstance().GetDevice()->CreateTexture(desc);
    }

private:
    const std::string ReadTextFile(const std::string & filename) {
        return std::string();
    }

    GPUShaderDescription ParseShaderFile(const std::string & filename) {
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

        GPUShaderProgram * vertexShader = Application::GetInstance().GetDevice()->CreateShaderProgram(vertexShaderProgramDesc);
        GPUShaderProgram * fragmentShader = Application::GetInstance().GetDevice()->CreateShaderProgram(fragmentShaderProgramDesc);

        GPUShaderDescription result;
        result.VertexShader = vertexShader;
        result.FragmentShader = fragmentShader;

        return result;
    }

private:
    std::string _root;
};
}

#endif