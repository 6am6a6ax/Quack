#include "quack/quack.h"

Quack::GPUShaderOpenGL::GPUShaderOpenGL(const Quack::GPUShaderDescription& desc) : GPUShader(desc)
{
    Create();
    AttachPrograms();
    if (!LinkAndCheckStatus()) {
        assert(true && GetInfoLog().c_str());
        Delete();
    }
    DetachPrograms();
}

Quack::GPUShaderOpenGL::~GPUShaderOpenGL() {
    Delete();
}

void Quack::GPUShaderOpenGL::Bind() const {
    glUseProgram(_resource);
}

void Quack::GPUShaderOpenGL::Unbind() const {
    glUseProgram(0);
}

void Quack::GPUShaderOpenGL::Create() {
    _resource = static_cast<unsigned>(glCreateProgram());
}

void Quack::GPUShaderOpenGL::Delete() const {
    glDeleteProgram(static_cast<GLuint>(_resource));
}

void Quack::GPUShaderOpenGL::Link() const {
    glLinkProgram(_resource);
}

bool Quack::GPUShaderOpenGL::IsLinked() const {
    GLint isLinked = 0;
    glGetProgramiv(_resource, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        return false;
    }

    return true;
}

bool Quack::GPUShaderOpenGL::LinkAndCheckStatus() const {
    Link();

    if (!IsLinked()) {
        return false;
    }
    
    return true;
}

std::string Quack::GPUShaderOpenGL::GetInfoLog() const {
    GLint lenght = 0;
    glGetProgramiv(_resource, GL_INFO_LOG_LENGTH, &lenght);

    std::vector<GLchar> log(lenght);
    glGetProgramInfoLog(_resource, lenght, &lenght, &log[0]);
    
    return std::string(log.begin(), log.end());
}

void Quack::GPUShaderOpenGL::AttachPrograms() const {
    if (_desc.VertexShader) {
        //glAttachShader(static_cast<GLuint>(_resource), static_cast<GLuint>(_desc.VertexShader->GetResource()));
        glAttachShader(_resource, _desc.VertexShader->GetResource());
    }
    // if (_desc.GeometryShader) {
    //     glAttachShader(static_cast<GLuint>(_resource), static_cast<GLuint>(_desc.GeometryShader->GetResource()));
    // }
    if (_desc.FragmentShader) {
        //glAttachShader(static_cast<GLuint>(_resource), static_cast<GLuint>(_desc.FragmentShader->GetResource()));
        glAttachShader(_resource, _desc.FragmentShader->GetResource());
    }
}

void Quack::GPUShaderOpenGL::DetachPrograms() const {
    if (_desc.VertexShader) {
        glDetachShader(static_cast<GLuint>(_resource), static_cast<GLuint>(_desc.VertexShader->GetResource()));
    }
    // if (_desc.GeometryShader) {
    //     glDetachShader(static_cast<GLuint>(_resource), static_cast<GLuint>(_desc.GeometryShader->GetResource()));
    // }
    if (_desc.FragmentShader) {
        glDetachShader(static_cast<GLuint>(_resource), static_cast<GLuint>(_desc.FragmentShader->GetResource()));
    }
}

GLint Quack::GPUShaderOpenGL::GetUniformLocation(const std::string& name) const {
    GLint location = glGetUniformLocation(_resource, name.c_str());
    // assert((location == -1) && "There is no uniform with exact name!");
    return location;
}

void Quack::GPUShaderOpenGL::UploadUniformInt(const std::string& name, int value) const {
    glUniform1i(GetUniformLocation(name), static_cast<GLint>(value));
}

void Quack::GPUShaderOpenGL::UploadUniformFloat(const std::string& name, float value) const {
    glUniform1f(GetUniformLocation(name), static_cast<GLfloat>(value));
}

void Quack::GPUShaderOpenGL::UploadUniformUnsigned(const std::string& name, unsigned value) const {
    glUniform1ui(GetUniformLocation(name), static_cast<GLuint>(value));
}

void Quack::GPUShaderOpenGL::UploadUniformVec2f(const std::string& name, const Quack::Vector2f& value) const {
    glUniform2f(GetUniformLocation(name), static_cast<GLfloat>(value.x), static_cast<GLfloat>(value.y));
}

void Quack::GPUShaderOpenGL::UploadUniformVec2i(const std::string& name, const Quack::Vector2i& value) const {
    glUniform2i(GetUniformLocation(name), static_cast<GLint>(value.x), static_cast<GLint>(value.y));
}

void Quack::GPUShaderOpenGL::UploadUniformVec2u(const std::string& name, const Quack::Vector2u& value) const {
    glUniform2ui(GetUniformLocation(name), static_cast<GLuint>(value.x), static_cast<GLuint>(value.y));
}

void Quack::GPUShaderOpenGL::UploadUniformVec2fArray(const std::string& name,
                                                     const std::vector<Quack::Vector2f>& container) const {
    glUniform2fv(GetUniformLocation(name), static_cast<GLsizei>(container.size()), 
                 reinterpret_cast<const GLfloat*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec2iArray(const std::string& name, 
                                                     const std::vector<Quack::Vector2i>& container) const {
    glUniform2iv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                 reinterpret_cast<const GLint*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec2uArray(const std::string& name, 
                                                     const std::vector<Quack::Vector2u>& container) const {
    glUniform2uiv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                  reinterpret_cast<const GLuint*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec3f(const std::string& name, const Quack::Vector3f& value) const {
    glUniform3f(GetUniformLocation(name), static_cast<GLfloat>(value.x), 
                                          static_cast<GLfloat>(value.y), 
                                          static_cast<GLfloat>(value.z));
}

void Quack::GPUShaderOpenGL::UploadUniformVec3i(const std::string& name, const Quack::Vector3i& value) const {
    glUniform3i(GetUniformLocation(name), static_cast<GLint>(value.x),
                                          static_cast<GLint>(value.y),
                                          static_cast<GLint>(value.z));
}

void Quack::GPUShaderOpenGL::UploadUniformVec3u(const std::string& name, const Quack::Vector3u& value) const {
    glUniform3ui(GetUniformLocation(name), static_cast<GLuint>(value.x),
                                           static_cast<GLuint>(value.y),
                                           static_cast<GLuint>(value.z));
}

void Quack::GPUShaderOpenGL::UploadUniformVec3fArray(const std::string& name, 
                                                     const std::vector<Quack::Vector3f>& container) const {
    glUniform3fv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                 reinterpret_cast<const GLfloat*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec3iArray(const std::string& name, 
                                                     const std::vector<Quack::Vector3i>& container) const {
    glUniform3iv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                 reinterpret_cast<const GLint*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec3uArray(const std::string& name, 
                                                     const std::vector<Quack::Vector3u>& container) const {
    glUniform3uiv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                reinterpret_cast<const GLuint*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec4f(const std::string& name, const Quack::Vector4f& value) const {
    glUniform4f(GetUniformLocation(name), static_cast<GLfloat>(value.x),
                                          static_cast<GLfloat>(value.y),
                                          static_cast<GLfloat>(value.z),
                                          static_cast<GLfloat>(value.w));
}

void Quack::GPUShaderOpenGL::UploadUniformVec4i(const std::string& name, const Quack::Vector4i& value) const {
    glUniform4i(GetUniformLocation(name), static_cast<GLint>(value.x),
                                          static_cast<GLint>(value.y),
                                          static_cast<GLint>(value.z),
                                          static_cast<GLint>(value.w));
}

void Quack::GPUShaderOpenGL::UploadUniformVec4u(const std::string& name, const Quack::Vector4u& value) const {
    glUniform4ui(GetUniformLocation(name), static_cast<GLuint>(value.x),
                                           static_cast<GLuint>(value.y),
                                           static_cast<GLuint>(value.z),
                                           static_cast<GLuint>(value.w));
}

void Quack::GPUShaderOpenGL::UploadUniformVec4fArray(const std::string& name, 
                                                     const std::vector<Quack::Vector4f>& container) const {
    glUniform4fv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                  reinterpret_cast<const GLfloat*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec4iArray(const std::string& name, 
                                                     const std::vector<Quack::Vector4i>& container) const {
    glUniform4iv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                  reinterpret_cast<const GLint*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformVec4uArray(const std::string& name, 
                                                     const std::vector<Quack::Vector4u>& container) const {
    glUniform4uiv(GetUniformLocation(name), static_cast<GLsizei>(container.size()),
                  reinterpret_cast<const GLuint*>(glm::value_ptr(container[0])));
}

void Quack::GPUShaderOpenGL::UploadUniformMat2f(const std::string& name, const Quack::Mat2f& value) const {
    glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat3f(const std::string& name, const Quack::Mat3f& value) const {
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat4f(const std::string& name, const Quack::Mat4f& value) const {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat2x3f(const std::string& name, const Quack::Mat2x3f& value) const {
    glUniformMatrix2x3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat3x2f(const std::string& name, const Quack::Mat3x2f& value) const {
    glUniformMatrix3x2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat2x4f(const std::string& name, const Quack::Mat2x4f& value) const {
    glUniformMatrix2x4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat4x2f(const std::string& name, const Quack::Mat4x2f& value) const {
    glUniformMatrix4x2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat3x4f(const std::string& name, const Quack::Mat3x4f& value) const {
    glUniformMatrix3x4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

void Quack::GPUShaderOpenGL::UploadUniformMat4x3f(const std::string& name, const Quack::Mat4x3f& value) const {
    glUniformMatrix4x3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(value)));
}

const char* GL_type_to_string(GLenum type) {
  switch(type) {
    case GL_BOOL: return "bool";
    case GL_INT: return "int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    default: break;
  }
  return "other";
}

Quack::IGPUShaderUniform::List& Quack::GPUShaderOpenGL::GetUniformList() const {
      int params = -1;
  glGetProgramiv(_resource, GL_LINK_STATUS, &params);
  printf("GL_LINK_STATUS = %i\n", params);
  
  glGetProgramiv(_resource, GL_ATTACHED_SHADERS, &params);
  printf("GL_ATTACHED_SHADERS = %i\n", params);
  
  glGetProgramiv(_resource, GL_ACTIVE_ATTRIBUTES, &params);
  printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
  for (int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib (
      _resource,
      i,
      max_length,
      &actual_length,
      &size,
      &type,
      name
    );
    if (size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetAttribLocation(_resource, long_name);
        printf("  %i) type:%s name:%s location:%i\n",
          i, GL_type_to_string(type), long_name, location);
      }
    } else {
      int location = glGetAttribLocation(_resource, name);
      printf("  %i) type:%s name:%s location:%i\n",
        i, GL_type_to_string(type), name, location);
    }
  }
    glGetProgramiv(_resource, GL_ACTIVE_UNIFORMS, &params);
    for (int i = 0; i < params; i++) {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;

        glGetActiveUniform(
            _resource,
            i,
            max_length,
            &actual_length,
            &size,
            &type,
            name
        );
        if(size > 1) {
        for(int j = 0; j < size; j++) {
            char long_name[64];
            sprintf(long_name, "%s[%i]", name, j);
            int location = glGetUniformLocation(_resource, long_name);
            printf("  %i) type:%s name:%s location:%i\n",
            i, GL_type_to_string(type), long_name, location);
        }
        } else {
        int location = glGetUniformLocation(_resource, name);
        printf("  %i) type:%s name:%s location:%i\n",
            i, GL_type_to_string(type), name, location);
        }
    }
    IGPUShaderUniform::List t;

    return t;
}