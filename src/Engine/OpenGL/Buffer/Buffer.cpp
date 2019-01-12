#include <Engine/Window/Window.h>
#include <iostream>
#include "Buffer.h"

GL::Buffer::Buffer() {
	glGenVertexArrays(1, &VAO);
}

void GL::Buffer::operator=(const GL::Buffer& buffer) {
	VAO = buffer.VAO;
	EBO = buffer.EBO;
	VBOs = buffer.VBOs;
	sequenceCount = buffer.sequenceCount;
}

void GL::Buffer::createIndeces() {
	glGenBuffers(1, &EBO);
}

void GL::Buffer::bind() const { 
	glBindVertexArray(VAO); 
}

void GL::Buffer::unbind() const { 
	glBindVertexArray(NULL); 
}

void GL::Buffer::create(int count) {
	for (int index = 0; index < count; index++) {
		VBOs.push_back(0);
		glGenBuffers(1, &VBOs.back());
	}
}

void GL::Buffer::setSequence(void * sequence, int count) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count,
		sequence, GL_STATIC_DRAW);
	this->sequenceCount = count;
}

void GL::Buffer::enableAttribute(int index) { glEnableVertexAttribArray(index); }

void GL::Buffer::disableAttribute(int index) { glDisableVertexAttribArray(index); }

void GL::Buffer::draw() const {
	glDrawElements(GL_TRIANGLES, sequenceCount, GL_UNSIGNED_INT, NULL);
}

void GL::Buffer::release() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(VBOs.size(), &VBOs[0]);
}