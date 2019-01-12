#include "Block.h"

Game::Block::Block(Game::BlockTemplate* block) : data(block) {}

void Game::Block::operator=(const Game::Block& block) {
	data = block.data;
}

void Game::Block::operator=(Game::BlockTemplate* block) {
	data = block;
}

void Game::Block::setBlockTemplate(Game::BlockTemplate* block) {
	data = block;
}

Game::BlockTemplate* Game::Block::getBlockTemplate() const {
	return data;
}