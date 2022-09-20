#include "quack/platform/opengl/gpu_shader_opengl.h"

#include <GL/glew.h>

Quack::GPUShaderOpenGL::GPUShaderOpenGL(const Quack::GPUShaderDescription & desc)
    : GPUShader(desc)
{
    _resource = glCreateProgram();

    glAttachShader(_resource, _desc.VertexShader->GetResource());
    glAttachShader(_resource, _desc.FragmentShader->GetResource());

    glLinkProgram(_resource);

    GLint isLinked = 0;
    glGetProgramiv(_resource, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(_resource, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(_resource, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(_resource);
        glDeleteProgram(_desc.VertexShader->GetResource());
        glDeleteProgram(_desc.FragmentShader->GetResource());
    }

    glDetachShader(_resource, _desc.VertexShader->GetResource());
    glDetachShader(_resource, _desc.FragmentShader->GetResource());
}

Quack::GPUShaderOpenGL::~GPUShaderOpenGL() {
    glDeleteProgram(_resource);
}

void Quack::GPUShaderOpenGL::Bind() const {
    glUseProgram(_resource);
}

void Quack::GPUShaderOpenGL::Unbind() const {
    glUseProgram(0);
}