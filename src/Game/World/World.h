#ifndef YACRAFT_GAME_WORLD
#define YACRAFT_GAME_WORLD

#include <map>
#include <thread>
#include "Engine/Camera/Camera.h"
#include "Engine/OpenGL/Shader/Shader.h"
#include "DataTypes/BiArray.h"
#include "Chunk.h"
#include "Math/FastNoise.h"

namespace Game {

	namespace World {

		extern GL::Shader WorldDrawShader;
		extern std::map<std::pair<int, int>, Chunk*> Chunks;
		extern int ProjectionSpaceInShader;
		extern int ViewSpaceInShader;
		extern int BlockAtlasInShader;
		extern int RenderDistance;
		extern std::thread GeneratorThread;
		extern Engine::Camera* GeneralPlayerCamera;
		extern std::vector<std::thread> ModelBuildThreads;
		extern glm::vec2 PreviousPosition;
		extern Math::FastNoise Noise;

		/**
		* @brief World initializing.
		**/
		void Init();

		/**
		* @brief Sets blocks in {X, Y, Z}.
		* @param X X coord of block.
		* @param Y Y coord of block.
		* @param Z Z coord of block.
		* @param block Block to set.
		**/
		void SetBlock(int X, int Y, int Z, BlockTemplate* block);

		/**
		* @brief Returns block in {X, Y, Z}.
		* @param X X coord of block.
		* @param Y Y coord of block.
		* @param Z Z coord of block.
		* @return Block.
		**/
		const Block& GetBlock(int X, int Y, int Z);

		/**
		* @brief Creates chunk in {X, Y}.
		**/
		void BuildChunkModel(int X, int Y);

		/**
		* @brief Function which checks GeneralPlayerCamera.position and creates world.
		**/
		void Generator();

		/**
		* @brief Generates chunk(X, Y) blocks.
		**/
		void Generate(int X, int Y);

		/**
		* @brief Draw world.
		**/
		void Draw();

		/**
		* @brief Updates world.
		**/
		void Update();

	};

};

#endif