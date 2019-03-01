#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <Engine/Window/Window.h>
#include <Engine/OpenGL/Types.h>
#include "ModelBuffer.h"

GL::ModelBuffer::ModelBuffer() 
	: GL::Buffer(){
	create(4);
}

void GL::ModelBuffer::setPositions(std::vector<glm::vec3>& glData) {
	vertexCount = glData.size();
	setData<glm::vec3>(0, glData.data(), glData.size());
	enableAttribute(0);                                              
	setAttribute<glm::vec3, GL::Types::FLOAT>(0, 3);
}

void GL::ModelBuffer::addPositions(std::vector<glm::vec3>& glData) {
	vertexCount += glData.size();
	addData<glm::vec3>(0, glData.data(), glData.size());
	enableAttribute(0);                                              
	setAttribute<glm::vec3, GL::Types::FLOAT>(0, 3);
}

void GL::ModelBuffer::setNormals(std::vector<glm::vec3>& glData) {
	setData<glm::vec3>(1, glData.data(), glData.size());
	enableAttribute(1);
	setAttribute<glm::vec3, GL::Types::FLOAT>(1, 3);
}

void GL::ModelBuffer::addNormals(std::vector<glm::vec3>& glData) {
	addData<glm::vec3>(1, glData.data(), glData.size());
	enableAttribute(1);
	setAttribute<glm::vec3, GL::Types::FLOAT>(1, 3);
}

void GL::ModelBuffer::setTexCoords(std::vector<glm::vec2>& glData) {
	setData<glm::vec2>(2, glData.data(), glData.size());
	enableAttribute(2);
	setAttribute<glm::vec2, GL::Types::FLOAT>(2, 2);
}

void GL::ModelBuffer::addTexCoords(std::vector<glm::vec2>& glData) {
	addData<glm::vec2>(2, glData.data(), glData.size());
	enableAttribute(2);
	setAttribute<glm::vec2, GL::Types::FLOAT>(2, 2);
}

void GL::ModelBuffer::setTangents(std::vector<glm::vec3>& glData) {
	setData<glm::vec3>(3, glData.data(), glData.size());
	enableAttribute(3);
	setAttribute<glm::vec3, GL::Types::FLOAT>(3, 3);
}

void GL::ModelBuffer::addTangents(std::vector<glm::vec3>& glData) {
	addData<glm::vec3>(3, glData.data(), glData.size());
	enableAttribute(3);
	setAttribute<glm::vec3, GL::Types::FLOAT>(3, 3);
}

void GL::ModelBuffer::setIndices(std::vector<unsigned int>& indices) {
	setSequence(&indices[0], indices.size());
}

void GL::ModelBuffer::drawArrays() {
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}