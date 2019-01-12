#include <iostream>
#include "BlockDefines.h"

Game::BlockTemplate* Game::Blocks::Air = nullptr;
Game::BlockTemplate* Game::Blocks::Dirt = nullptr;
Game::BlockTemplate* Game::Blocks::Grass = nullptr;

void Game::Blocks::Init() {
	Air = new BlockTemplate();
	Air->setType(-1);
	Air->setName("Air");

	Dirt = new BlockTemplate();
	Dirt->setUpTexCoords({ 0, 0 });
	Dirt->setDownTexCoords({ 0, 0 });
	Dirt->setLeftTexCoords({ 0, 0 });
	Dirt->setRightTexCoords({ 0, 0 });
	Dirt->setBackTexCoords({ 0, 0 });
	Dirt->setFrontTexCoords({ 0, 0 });
	Dirt->setType(1);
	Dirt->setName("Dirt");

	Grass = new BlockTemplate();
	Grass->setUpTexCoords({ 32, 0 });
	Grass->setDownTexCoords({ 0, 0 });
	Grass->setLeftTexCoords({ 16, 0 });
	Grass->setRightTexCoords({ 16, 0 });
	Grass->setBackTexCoords({ 16, 0 });
	Grass->setFrontTexCoords({ 16, 0 });
	Grass->setType(1);
	Grass->setName("Grass");
}