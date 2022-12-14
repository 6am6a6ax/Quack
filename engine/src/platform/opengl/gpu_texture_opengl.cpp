#include "quack/quack.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Quack::GPUTextureOpenGL::GPUTextureOpenGL(const Quack::GPUTextureDescription & desc) : GPUTexture(desc) {
    int width, height, channels;
    stbi_uc * data = stbi_load(desc.Path.c_str(), &width, &height, &channels, 0);

    if (!data) {
        data = stbi_load("/home/bujhm/dev/cpp/cg/quack/engine/assets/textures/no_texture.png", &width, &height, &channels, 0);
    }
    
    _desc.Width = width;
    _desc.Height = height;

    glCreateTextures(GL_TEXTURE_2D, 1, &_resource);
    glTextureStorage2D(_resource, 1, GL_RGB8, _desc.Width, _desc.Height);

    glTextureParameteri(_resource, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(_resource, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(_resource, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(_resource, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTextureSubImage2D(_resource, 0, 0, 0, _desc.Width, _desc.Height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Quack::GPUTextureOpenGL::~GPUTextureOpenGL() {
    glDeleteTextures(1, &_resource);
}

void Quack::GPUTextureOpenGL::Bind() const {
    glBindTextureUnit(0, _resource);
}

void Quack::GPUTextureOpenGL::Unbind() const {
    //glBindTextureUnit(0, _resource);
}
