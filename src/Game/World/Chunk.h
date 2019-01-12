#ifndef YACRAFT_GAME_CHUNK
#define YACRAFT_GAME_CHUNK

#include <iostream>
#include <Engine/OpenGL/Buffer/ModelBuffer.h>
#include "ChunkSegment.h"

namespace Game {

	class Chunk {
	private:
		std::vector<ChunkSegment> segments;
		std::vector<glm::vec3> vertexPositions;
		std::vector<glm::vec3> vertexNormals;
		std::vector<glm::vec2> vertexTexCoords;
		GL::ModelBuffer buffer;
		bool blocksUpdated = true;
		bool meshUpdated = true;
		bool terrainGenerated = false;

	public:
		Chunk();

		void operator=(const Chunk& chunk);

		/**
		* @brief Returns block in {X, Y, Z}.
		* @param X X coord of block.
		* @param Y Y coord of block.
		* @param Z Z coord of block.
		* @return Block.
		**/
		const Block& getBlock(unsigned int X, unsigned int Y, unsigned int Z) const;

		/**
		* @brief Sets blocks in {X, Y, Z}.
		* @param X X coord of block.
		* @param Y Y coord of block.
		* @param Z Z coord of block.
		* @param block Block to set.
		**/
		void setBlock(unsigned int X, unsigned int Y, unsigned int Z, BlockTemplate* block);

		/**
		* @brief Sets vertex positions for mesh;
		* @param positions Vertex positions;
		**/
		void setVertexPositions(std::vector<glm::vec3>& positions);

		/**
		* @brief Sets vertex normals for mesh.
		* @param normals Vertex normals.
		**/
		void setVertexNormals(std::vector<glm::vec3>& normals);

		/**
		* @brief Sets vertex texture coords for mesh.
		* @param texCoords Vertex texture coords.
		**/
		void setVertexTexCoords(std::vector<glm::vec2>& texCoords);

		/**
		* @brief Returns chunk segments.
		* @return Chunk segments.
		**/
		const std::vector<ChunkSegment>& getSegments() const;

		/**
		* @brief Draws chunk.
		**/
		void draw();

		/**
		* @brief Is blocks in chunk are setted?
		* @return true if blocks was setted.
		**/
		bool isBlocksUpdated();

		/**
		* @brief Sets blocks "setted".
		* @param value True if "setted".
		**/
		void setBlocksUpdated(bool value);

		/**
		* @brief Is terrain was generated?
		* @return True if it was generated.
		**/
		bool isTerrainGenerated();

		/**
		* @brief Set terrain generated.
		* @param value True or false...
		**/
		void setTerrainGenerated(bool value);

		/**
		* @brief Is mesh was changed?
		* @return True if it was changed.
		**/
		bool isMeshUpdated();

		/**
		* @brief Sets mesh "updated".
		* @param value True or false...
		**/
		void setMeshUpdated(bool value);
	};

};

#endif