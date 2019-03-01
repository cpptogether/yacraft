#include <string>
#include <iostream>
#include "Chunk.h"
#include "Game/Global.h"

Game::Chunk::Chunk()
	: buffer(GL::ModelBuffer())
	, segments(1){}

void Game::Chunk::setBlocksUpdated(bool value){
	blocksUpdated = value;
}

bool Game::Chunk::isBlocksUpdated() {
	return blocksUpdated;
}

bool Game::Chunk::isMeshUpdated(){
	return meshUpdated;
}

void Game::Chunk::setMeshUpdated(bool value){
	meshUpdated = value;
}

const std::vector<Game::ChunkSegment>& Game::Chunk::getSegments() const {
	return segments;
}

void Game::Chunk::setTerrainGenerated(bool value){
	terrainGenerated = value;
}

bool Game::Chunk::isTerrainGenerated(){
	return terrainGenerated;
}

void Game::Chunk::draw() {
	buffer.bind();
	if (meshUpdated) {
		buffer.setPositions(vertexPositions);
		buffer.setNormals(vertexNormals);
		buffer.setTexCoords(vertexTexCoords);
		vertexPositions = std::vector<glm::vec3>();
		vertexNormals = std::vector<glm::vec3>();
		vertexTexCoords = std::vector<glm::vec2>();
		meshUpdated = false;
	}
	buffer.drawArrays();
	buffer.unbind();
}

void Game::Chunk::setBlock(unsigned int X, unsigned int Y, unsigned int Z, Game::BlockTemplate* block) {
	if ((Y / CHUNK_SEGMENT_SIZE) + 1 >= segments.size()) {
		for (int counter = segments.size() - 1; counter <= (Y / CHUNK_SEGMENT_SIZE) + 1; counter++) {
			segments.push_back(ChunkSegment());
		}
	}
	segments[Y / CHUNK_SEGMENT_SIZE].setBlock(X, Y % CHUNK_SEGMENT_SIZE, Z, block);
	blocksUpdated = true;
}

const Game::Block& Game::Chunk::getBlock(unsigned int X, unsigned int Y, unsigned int Z) const{
	return segments[Y / CHUNK_SEGMENT_SIZE].getBlock(X, Y % CHUNK_SEGMENT_SIZE, Z);
}

void Game::Chunk::operator=(const Game::Chunk& chunk) {
	segments = chunk.segments;
	buffer = chunk.buffer;
}

void Game::Chunk::setVertexPositions(std::vector<glm::vec3>& positions){
	vertexPositions = positions;
}

void Game::Chunk::setVertexNormals(std::vector<glm::vec3>& normals){
	vertexNormals = normals;
}

void Game::Chunk::setVertexTexCoords(std::vector<glm::vec2>& texCoords){
	vertexTexCoords = texCoords;
}