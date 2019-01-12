#include <Engine/Window/Window.h>
#include "Texture.h"

GL::Texture::Texture(unsigned int ID, unsigned int width, unsigned int height) {
	this->ID = ID;
	size.x = width;
	size.y = height;
}

GL::Texture::Texture(const Texture& texture) {
	ID = texture.ID;
	activeUnit = texture.activeUnit;
	type = texture.type;
	path = texture.path;
	size = texture.size;
}

GL::Texture::Texture() {

}

void GL::Texture::operator=(const Texture& texture) {
	ID = texture.ID;
	activeUnit = texture.activeUnit;
	type = texture.type;
	path = texture.path;
	size = texture.size;
}

const std::string & GL::Texture::getPath() const {
	return path;
}

const std::string & GL::Texture::getType() const {
	return type;
}

void GL::Texture::setType(const std::string & type) {
	this->type = type;
}

const unsigned int GL::Texture::getID() const {
	return ID;
}

const glm::vec2& GL::Texture::getSize() const {
	return size;
}

void GL::Texture::setActiveUnit(int argActiveUnit) {
	glActiveTexture(GL_TEXTURE0 + argActiveUnit);
	activeUnit = argActiveUnit;
}

void GL::Texture::setActiveUnit(int activeUnit) const {
	glActiveTexture(GL_TEXTURE0 + activeUnit);
}

int GL::Texture::getActiveUnit() const {
	return activeUnit;
}

void GL::Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GL::Texture::bind(int unit) const {
	setActiveUnit(unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GL::Texture::bind(int unit) {
	setActiveUnit(unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GL::Texture::release() {
	glDeleteTextures(1, &ID);
}