#ifndef QUACK_SHADER_UNIFORM_OPENGL_H
#define QUACK_SHADER_UNIFORM_OPENGL_H

#include <cstdint>
#include <memory>
#include "quack/graphics/gpu_shader_uniform.h"

namespace Quack {
class GPUShaderUniformOpenGL final : public IGPUShaderUniform {
public:
    enum class Type : uint8_t {
        NONE,
        BOOL, INT32, FLOAT32, STRUCT,
        VEC2, VEC3, VEC4,
        MAT3, MAT4
    };

public:
    GPUShaderUniformOpenGL(GPUShaderDomain domain, Type type, const std::string& name, uint32_t count = 1);
    ~GPUShaderUniformOpenGL() override;

public:
    bool IsArray() const;

public:
    const std::string& GetName() const override;
    GPUShaderDomain GetDomain() const override;

    uint32_t GetSize() const override;
    uint32_t GetCount() const override;
    uint32_t GetOffset() const override;

public:
    static uint32_t GetSizeOfType(Type type);

public:
    Type GetType() const;
    int32_t GetLocation() const;
    uint32_t GetAbsoluteOffset() const;
    const std::shared_ptr<ShaderStruct>& GetShaderStruct() const;

public:
    void SetOffset(uint32_t offset) override;

private:
    GPUShaderDomain _domain;
    Type _type;
    std::string _name;
    std::shared_ptr<ShaderStruct> _struct;

    uint32_t _count;
    uint32_t _offset;
    int32_t _location;
    uint32_t _size;
};
}

#endif