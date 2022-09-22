#include "quack/platform/opengl/gpu_framebuffer_opengl.h"

#include <GL/glew.h>

#include <iostream>

Quack::GPUFramebufferOpenGL::GPUFramebufferOpenGL(const Quack::GPUFramebufferDescription & desc)
    : GPUFramebuffer(desc)
{
    Invalidate();
}

Quack::GPUFramebufferOpenGL::~GPUFramebufferOpenGL() {
    glDeleteFramebuffers(1, &_resource);
}

void Quack::GPUFramebufferOpenGL::Invalidate() {
    glCreateFramebuffers(1, &_resource);
    glBindFramebuffer(GL_FRAMEBUFFER, _resource);

    glCreateTextures(GL_TEXTURE_2D, 1, &_desc.ColorAttachment);
    glBindTexture(GL_TEXTURE_2D, _desc.ColorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _desc.FrameSize.Width, _desc.FrameSize.Height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _desc.ColorAttachment, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &_desc.DepthAttachment);
    glBindTexture(GL_TEXTURE_2D, _desc.DepthAttachment);
    //glTextureStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _desc.FrameSize.Width, _desc.FrameSize.Height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _desc.FrameSize.Width, _desc.FrameSize.Height, 0,
                 GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _desc.DepthAttachment, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "GL_FRAMEBUFFER_COMPLETE\n";
    }
    else {
        std::cout << "GL_FRAMEBUFFER_FAILED\n";
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Quack::GPUFramebufferOpenGL::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, _resource);
}

void Quack::GPUFramebufferOpenGL::Unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}