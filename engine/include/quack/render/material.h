// #ifndef QUACK_MATERIAL_H
// #define QUACK_MATERIAL_H

// #include <cstddef>
// #include <cstring>
// #include <memory>

// #include "quack/graphics/gpu_shader.h"

// namespace Quack {
// class UniformBuffer {
// public:
//     UniformBuffer() : _data(nullptr), _size(0) {}
//     UniformBuffer(size_t size) : _data(nullptr), _size(size) {
//         _data = new std::byte[size];
//     }

//     template<typename T>
//     T& Read(size_t offset = 0) {
//         return *(reinterpret_cast<T*>(_data + offset));
//     }

//     template<typename T>
//     void Write(const T& data, size_t size, size_t offset) {
//         memcpy(_data + offset, reinterpret_cast<const void*>(data), size);
//     }

//     void Empty() {
//         delete[] _data;
//         _data = nullptr;
//         _size = 0;
//     }

//     std::size_t GetSize() const { return _size; }

// private:
//     std::byte* _data; 
//     std::size_t _size;
// };

// class Material {
// public:
//     Material(const std::shared_ptr<GPUShader>& shader);

// public:
//     void Bind() const;
//     void Unbind() const;

// public:
//     template<typename T>
//     void Set(const std::string & name, const T& value) {
//         auto desc = GetShaderUniformDescription(name);
//         _uniformBuffer.Write(value, desc.Size, desc.Offset);
//     }

//     template<typename T>
//     T& Get(const std::string& name) {
//         auto desc = GetShaderUniformDescription(name);
//         return _uniformBuffer.Read<T>(desc.Offset);
//     }

// public:
//     std::shared_ptr<GPUShader>& GetShader() const;
//     void SetShader(const std::shared_ptr<GPUShader>& shader);

// private:
//     GPUShaderUniformDescription GetShaderUniformDescription(const std::string& name) const {
//         auto descs = _shader->GetUniformList();
//         for (auto& desc : descs) {
//             if (desc.Name == name) {
//                 return desc;
//             }
//         }
//         return GPUShaderUniformDescription();
//     }

// private:
//     std::shared_ptr<GPUShader> _shader;
//     UniformBuffer _uniformBuffer;
// };

// class MaterialInstance {
// public:
//     MaterialInstance(const std::shared_ptr<Material>& material);

// public:
//     std::shared_ptr<Material>& GetMaterial() const;
//     void SetMaterial(const std::shared_ptr<Material>& material);

// private:
//     std::shared_ptr<Material> _material;
// };
// }

// #endif