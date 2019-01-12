#include "BlockTemplate.h"
#include <glm/glm.hpp>
#include "Game/Global.h"

bool Game::BlockTemplate::operator==(const Game::BlockTemplate& blockTemplate) {
	if (type == blockTemplate.type) {
		return false;
	}

	if (backTexCoord == blockTemplate.backTexCoord) {
		return false;
	}

	if (frontTexCoord == blockTemplate.frontTexCoord) {
		return false;
	}

	if (leftTexCoord == blockTemplate.leftTexCoord) {
		return false;
	}

	if (rightTexCoord == blockTemplate.rightTexCoord) {
		return false;
	}

	if (bottomTexCoord == blockTemplate.bottomTexCoord) {
		return false;
	}

	if (topTexCoord == blockTemplate.topTexCoord) {
		return false;
	}

	return true;
}

void Game::BlockTemplate::setName(const std::string& string){
	name = string;
}

const std::string& Game::BlockTemplate::getName(){
	return name;
}

void Game::BlockTemplate::setBackTexCoords(const glm::vec2& texCoord) {
	backTexCoord = texCoord / Global::BlockAtlas.getSize();
}

const glm::vec2& Game::BlockTemplate::getBackTexCoords() const {
	return backTexCoord;
}

void Game::BlockTemplate::setFrontTexCoords(const glm::vec2& texCoord) {
	frontTexCoord = texCoord / Global::BlockAtlas.getSize();
}

const glm::vec2& Game::BlockTemplate::getFrontTexCoords() const {
	return frontTexCoord;
}

void Game::BlockTemplate::setLeftTexCoords(const glm::vec2& texCoord) {
	leftTexCoord = texCoord / Global::BlockAtlas.getSize();
}

const glm::vec2& Game::BlockTemplate::getLeftTexCoords() const {
	return leftTexCoord;
}

void Game::BlockTemplate::setRightTexCoords(const glm::vec2& texCoord) {
	rightTexCoord = texCoord / Global::BlockAtlas.getSize();
}

const glm::vec2& Game::BlockTemplate::getRightTexCoords() const {
	return rightTexCoord;
}

void Game::BlockTemplate::setDownTexCoords(const glm::vec2& texCoord) {
	bottomTexCoord = texCoord / Global::BlockAtlas.getSize();
}

const glm::vec2& Game::BlockTemplate::getDownTexCoords() const {
	return bottomTexCoord;
}

void Game::BlockTemplate::setUpTexCoords(const glm::vec2& texCoord) {
	topTexCoord = texCoord / Global::BlockAtlas.getSize();
}

const glm::vec2& Game::BlockTemplate::getUpTexCoords() const {
	return topTexCoord;
}

void Game::BlockTemplate::setType(int type) {
	this->type = type;
}

int Game::BlockTemplate::getType() const {
	return type;
}