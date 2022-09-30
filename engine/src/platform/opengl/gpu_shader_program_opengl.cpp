#include "quack/quack.h"

static GLint ShaderProgramTypeToOpenGLType(const Quack::ShaderProgramType & shaderProgramType) {
    switch (shaderProgramType) {
        case Quack::ShaderProgramType::Vertex:
            return GL_VERTEX_SHADER;
        case Quack::ShaderProgramType::Fragment:
            return GL_FRAGMENT_SHADER;
    }
}

Quack::GPUShaderProgramOpenGL::GPUShaderProgramOpenGL(const Quack::GPUShaderProgramDescription & desc)
    : GPUShaderProgram(desc)
{
    _resource = glCreateShader(ShaderProgramTypeToOpenGLType(_desc.Type));

    const GLchar * src = (const GLchar *)(_desc.Source.c_str());
    glShaderSource(_resource, 1, &src, 0);
    glCompileShader(_resource);

    GLint isCompiled = 0;
    glGetShaderiv(_resource, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(_resource, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(_resource, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(_resource);

        // TODO: Debug
        std::cout << infoLog.data();
    }
}

Quack::GPUShaderProgramOpenGL::~GPUShaderProgramOpenGL() {
    glDeleteProgram(_resource);
}

void Quack::GPUShaderProgramOpenGL::Bind() const {

}

void Quack::GPUShaderProgramOpenGL::Unbind() const {

}
