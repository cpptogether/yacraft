#include "Game/Block/BlockDefines.h"
#include "ChunkSegment.h"

Game::ChunkSegment::ChunkSegment(){
	for(int X = 0; X < CHUNK_SEGMENT_SIZE; X++){
		for(int Y = 0; Y < CHUNK_SEGMENT_SIZE; Y++){
			for(int Z = 0; Z < CHUNK_SEGMENT_SIZE; Z++){
				blocks[X][Y][Z] = Blocks::Air;
			}
		}
	}
}

void Game::ChunkSegment::operator=(const Game::ChunkSegment& segment) {
	blocks = segment.blocks;
}

const Game::Block& Game::ChunkSegment::getBlock(unsigned int X, unsigned int Y, unsigned int Z) const {
	return blocks[X][Y][Z];
}

void Game::ChunkSegment::setBlock(unsigned int X, unsigned int Y, unsigned int Z, Game::BlockTemplate* blockTemplate) {
	blocks[X][Y][Z].setBlockTemplate(blockTemplate);
}