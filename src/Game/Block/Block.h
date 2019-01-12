#ifndef YACRAFT_GAME_BLOCK
#define YACRAFT_GAME_BLOCK

#include "BlockTemplate.h"
#include "BlockDefines.h"

namespace Game {
	
	/**
	* @brief Block. Its have info to draw <sideName\> side or not, needs BlockTemplate to life.
	**/
	class Block {
	private:
		BlockTemplate* data = Blocks::Air;
	public:
		Block(BlockTemplate* block = nullptr);

		void operator=(const Block& block);

		void operator=(BlockTemplate* data);

		/**
		* @brief Sets block template.
		* @param data Block template to set.
		**/
		void setBlockTemplate(BlockTemplate* data);

		/**
		* @brief Gets block template.
		* @returns Game::BlockTemplate Block template.
		**/
		BlockTemplate* getBlockTemplate() const;
	};

};

#endif