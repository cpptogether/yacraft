
#include <iostream>
#include <Engine/Window/Window.h>
#include <Engine/OpenGL/Texture/Texture.h>
#include "Framebuffer.h"

GL::Framebuffer::Framebuffer(const Framebuffer & buffer) {
	FBO = buffer.FBO;
	RBO = buffer.RBO;
	width = buffer.width;
	height = buffer.height;
	texture = buffer.texture;
}

void GL::Framebuffer::operator =(const Framebuffer & buffer) {
	FBO = buffer.FBO;
	RBO = buffer.RBO;
	width = buffer.width;
	height = buffer.height;
	texture = buffer.texture;
}

void GL::Framebuffer::initialize(unsigned int width, unsigned int height) {
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, textureColorbuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width,
		height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	FBO = framebuffer;
	RBO = rbo;
	texture = textureColorbuffer;

	this->width = width;
	this->height = height;
}

void GL::Framebuffer::bind() const { glBindFramebuffer(GL_FRAMEBUFFER, FBO); }

GL::Texture GL::Framebuffer::getTexture() const{
	return GL::Texture(texture, width, height);
}

void GL::Framebuffer::ClearColorBuffer() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void GL::Framebuffer::ClearDepthBuffer() {
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GL::Framebuffer::EnableDepthTest() {
	glEnable(GL_DEPTH_TEST);
}

void GL::Framebuffer::DisableDepthTest() {
	glDisable(GL_DEPTH_TEST);
}

void GL::Framebuffer::EnableFaceCulling() {
	glEnable(GL_CULL_FACE);
}

void GL::Framebuffer::DisableFaceCulling() {
	glDisable(GL_CULL_FACE);
}

void GL::Framebuffer::SetClearColor(const glm::vec4 & color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void GL::Framebuffer::BindDefault() { glBindFramebuffer(GL_FRAMEBUFFER, NULL); }

char * GL::Framebuffer::ReadPixels(unsigned int width, unsigned int height) {
	char* pixels;
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_INT_8_8_8_8,
		pixels);
	return pixels;
}