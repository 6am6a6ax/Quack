#ifndef QUACK_GPU_SHADER_UNIFORM_H
#define QUACK_GPU_SHADER_UNIFORM_H

#include <cstdint>
#include <memory>
namespace Quack {
enum class GPUShaderDomain : std::uint32_t {
    Vertex, Fragment
};

class IGPUShaderAttribute {

};

class IGPUShaderUniform {
public:
    virtual ~IGPUShaderUniform() = 0;

public:
    using List = std::vector<std::shared_ptr<IGPUShaderUniform>>;

    using Iterator = std::vector<IGPUShaderUniform>::iterator;
    using ConstIterator = std::vector<IGPUShaderUniform>::const_iterator;

public:
    virtual const std::string& GetName() const = 0;

    virtual uint32_t GetSize() const = 0;
    virtual uint32_t GetCount() const = 0;
    virtual uint32_t GetOffset() const = 0;

    virtual GPUShaderDomain GetDomain() const = 0;

public:
    virtual void SetOffset(uint32_t) = 0;
};

class IGPUShaderUniformBuffer {

};

class IGPUShaderResource {

};

class ShaderStruct {
public:
    explicit ShaderStruct(const std::string& name);

public:
    void Push(const std::shared_ptr<IGPUShaderUniform>& field);

public:
    const std::string& GetName() const;

    uint32_t GetSize() const;
    uint32_t GetOffset() const;

    const IGPUShaderUniform::List& GetFields() const;

public:
    void SetOffset(uint32_t offset);

private:
    std::string _name;

    uint32_t _size;
    uint32_t _offset;

    IGPUShaderUniform::List _fields;
};
}

#endif