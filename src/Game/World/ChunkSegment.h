#ifndef YACRAFT_GAME_CHUNK_SEGMENT
#define YACRAFT_GAME_CHUNK_SEGMENT

#include <array>
#include "Game/Block/Block.h"

namespace Game {

	static constexpr int CHUNK_SEGMENT_SIZE = 16;

	/*
	* @brief Segment of chunk. Easier to manipulate.
	*/
	class ChunkSegment {
	private:
		Block blocks[CHUNK_SEGMENT_SIZE][CHUNK_SEGMENT_SIZE][CHUNK_SEGMENT_SIZE];

	public:

		ChunkSegment();

		/*
		* @brief Gets block.
		* @param X X-coord of block in this chunk segment.
		* @param Y Y-coord of block in this chunk segment.
		* @returns Game::Block Block.
		*/
		const Block& getBlock(unsigned int X, unsigned int Y, unsigned int Z) const;

		/*
		* @brief Sets block.
		* @param X X-coord of block in this chunk segment.
		* @param Y Y-coord of block in this chunk segment.
		* @param block Block to set.
		*/
		void setBlock(unsigned int X, unsigned int Y, unsigned int Z, BlockTemplate* blockTemplate);
	};

};

#endif