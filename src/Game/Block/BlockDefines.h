#ifndef YACRAFT_GAME_BLOCK_DEFINES
#define YACRAFT_GAME_BLOCK_DEFINES

#include "BlockTemplate.h"

namespace Game {

	namespace Blocks {

		extern BlockTemplate* Air;
		extern BlockTemplate* Dirt;
		extern BlockTemplate* Grass;

		/**
		* @brief Initialized blocks defines.
		**/
		void Init();

	};

};

#endif