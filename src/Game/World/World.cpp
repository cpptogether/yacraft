
#include <glm/gtc/matrix_transform.hpp>
#include "Game/Block/BlockDefines.h"
#include "Game/Global.h"
#include "World.h"

GL::Shader Game::World::WorldDrawShader;
std::map<std::pair<int, int>, Game::Chunk*> Game::World::Chunks;
int Game::World::ProjectionSpaceInShader = 0;
int Game::World::ViewSpaceInShader = 0;
int Game::World::BlockAtlasInShader = 0;
int Game::World::RenderDistance = 32;
std::thread Game::World::GeneratorThread;
Engine::Camera* Game::World::GeneralPlayerCamera;
std::vector<std::thread> Game::World::ModelBuildThreads;
glm::vec2 Game::World::PreviousPosition = glm::vec2(-99999, -99999);
Math::FastNoise Game::World::Noise;

void Game::World::Update(){
	PreviousPosition = glm::vec2(GeneralPlayerCamera->getPosition().x + GeneralPlayerCamera->getPosition().y);
}

void Game::World::Generator(){
	while(Window::IsOpen()){
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		glm::vec3 pos = GeneralPlayerCamera->getPosition();
		int CameraX = pos.x / CHUNK_SEGMENT_SIZE;
		int CameraY = pos.z / CHUNK_SEGMENT_SIZE;

		if(PreviousPosition == glm::vec2(CameraX, CameraY)){
			continue;
		}

		for (int X = CameraX - RenderDistance; X <= CameraX + RenderDistance; X++) {
			for (int Y = CameraY - RenderDistance; Y <= CameraY + RenderDistance; Y++) {
				if (Chunks.find({ X, Y }) != Chunks.end()) {
					Generate(X, Y);
				}
			}
		}

		for(int X = CameraX - RenderDistance; X <= CameraX + RenderDistance; X++){
			for(int Y = CameraY - RenderDistance; Y <= CameraY + RenderDistance; Y++){
				if(Chunks.find({ X, Y }) != Chunks.end()){
					if (Chunks[{ X, Y }]->isBlocksUpdated()) {
						BuildChunkModel(X, Y);
					}
				}
			}
		}

		PreviousPosition = {CameraX, CameraY};
	}
}

void Game::World::Init() {
	WorldDrawShader.setVertex("res/Shaders/Simple.vs");
	WorldDrawShader.setFragment("res/Shaders/Simple.fs");
	WorldDrawShader.compile();
	ProjectionSpaceInShader = WorldDrawShader.getUniformPosition("projection");
	ViewSpaceInShader = WorldDrawShader.getUniformPosition("view");
	BlockAtlasInShader = WorldDrawShader.getUniformPosition("blockAtlas");
	GeneratorThread = std::thread(Generator);
	GeneratorThread.detach();
	Noise.SetNoiseType(Noise.Cellular);
}

void Game::World::SetBlock(int X, int Y, int Z, Game::BlockTemplate* block) {
	Chunks[{ X / CHUNK_SEGMENT_SIZE, Z / CHUNK_SEGMENT_SIZE }]->setBlock(
		X % CHUNK_SEGMENT_SIZE, Y, Z % CHUNK_SEGMENT_SIZE, block);
}

const Game::Block& Game::World::GetBlock(int X, int Y, int Z) {
	return Chunks[{ X / CHUNK_SEGMENT_SIZE, Z / CHUNK_SEGMENT_SIZE }]->getBlock(
		X % CHUNK_SEGMENT_SIZE, Y, Z % CHUNK_SEGMENT_SIZE);
}

void Game::World::Generate(int X, int Y) {
	Chunk* chunk = Chunks[{X, Y}];

	if(chunk->isTerrainGenerated()){
		return;
	}

	int worldXOffset = X * CHUNK_SEGMENT_SIZE;
	int worldYOffset = Y * CHUNK_SEGMENT_SIZE;

	for (int X = 0; X < CHUNK_SEGMENT_SIZE; X++) {
		for (int Z = 0; Z < CHUNK_SEGMENT_SIZE; Z++) {
			int height = std::abs(Noise.GetPerlin(worldXOffset + X, worldYOffset + Z) * 50);
			for (int Y = 0; Y < height; Y++) {
				chunk->setBlock(X, Y, Z, Blocks::Dirt);
			}
		}
	}

	for (int X = 0; X < CHUNK_SEGMENT_SIZE; X++) {
		for (int Z = 0; Z < CHUNK_SEGMENT_SIZE; Z++) {
			int height = std::abs(Noise.GetPerlin(worldXOffset + X, worldYOffset + Z) * 50);
			chunk->setBlock(X, height, Z, Blocks::Grass);
		}
	}

	chunk->setTerrainGenerated(true);
}

void Game::World::BuildChunkModel(int chunkX, int chunkY) {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	Chunk* chunk = Chunks[{chunkX, chunkY}];

	bool chunkExist[4] = { false };
	Chunk* chunks[4] = { nullptr };

	if(Chunks.find({ chunkX - 1, chunkY }) != Chunks.end()) {
		chunks[0] = Chunks[{ chunkX - 1, chunkY }];
		chunkExist[0] = chunks[0]->isTerrainGenerated();
	}

	if(Chunks.find({ chunkX + 1, chunkY }) != Chunks.end()) {
		chunks[2] = Chunks[{ chunkX + 1, chunkY }];
		chunkExist[2] = chunks[2]->isTerrainGenerated();
	}

	if(Chunks.find({ chunkX, chunkY - 1 }) != Chunks.end()) {
		chunks[1] = Chunks[{ chunkX, chunkY - 1 }];
		chunkExist[1] = chunks[1]->isTerrainGenerated();
	}

	if(Chunks.find({ chunkX, chunkY + 1 }) != Chunks.end()) {
		chunks[3] = Chunks[{ chunkX, chunkY + 1 }];
		chunkExist[3] = chunks[3]->isTerrainGenerated();
	}

	if((chunkExist[0] && chunkExist[1] && chunkExist[2] && chunkExist[3]) == false){
		if(chunkExist[0]){
			chunks[0]->setBlocksUpdated(true);
		}

		if(chunkExist[1]){
			chunks[1]->setBlocksUpdated(true);
		}

		if(chunkExist[2]){
			chunks[2]->setBlocksUpdated(true);
		}

		if(chunkExist[3]){
			chunks[3]->setBlocksUpdated(true);
		}
	}

	auto segments = chunk->getSegments();

	int inWorldX = chunkX * CHUNK_SEGMENT_SIZE;
	int inWorldZ = chunkY * CHUNK_SEGMENT_SIZE;
	int vertexCount = 0;

	for (int X = 0; X < CHUNK_SEGMENT_SIZE; X++) {
		for (int Y = 0; Y < CHUNK_SEGMENT_SIZE * segments.size(); Y++) {
			for (int Z = 0; Z < CHUNK_SEGMENT_SIZE; Z++) {
				const Block& block = chunk->getBlock(X, Y, Z);

				if (block.getBlockTemplate() == Blocks::Air) {
					continue;
				}

				bool leftDrawable = false;
				bool rightDrawable = false;
				bool upDrawable = false;
				bool downDrawable = false;
				bool backDrawable = false;
				bool frontDrawable = false;

				int blockType = block.getBlockTemplate()->getType();

				if (Y / CHUNK_SEGMENT_SIZE >= segments.size()) {
					continue;
				}

				if (X > 0) {
					if (chunk->getBlock(X - 1, Y, Z).getBlockTemplate()->getType() != blockType) {
						leftDrawable = true;
					}
				}
				else {
					if (chunkExist[0]) {
						if (chunks[0]->getBlock(CHUNK_SEGMENT_SIZE - 1, Y, Z).getBlockTemplate()->getType() != blockType) {
							leftDrawable = true;
						}
					}
				}

				if (X < CHUNK_SEGMENT_SIZE - 1) {
					if (chunk->getBlock(X + 1, Y, Z).getBlockTemplate()->getType() != blockType) {
						rightDrawable = true;
					}
				}
				else {
					if (chunkExist[2]) {
						if (chunks[2]->getBlock(0, Y, Z).getBlockTemplate()->getType() != blockType) {
							rightDrawable = true;
						}
					}
				}

				if (Y > 0) {
					if (chunk->getBlock(X, Y - 1, Z).getBlockTemplate()->getType() != blockType) {
						downDrawable = true;
					}
				}

				
				if (chunk->getBlock(X, Y + 1, Z).getBlockTemplate()->getType() != blockType) {
					upDrawable = true;
				}

				if (Z > 0) {
					if (chunk->getBlock(X, Y, Z - 1).getBlockTemplate()->getType() != blockType) {
						backDrawable = true;
					}
				}
				else {
					if (chunkExist[1]) {
						if (chunks[1]->getBlock(X, Y, CHUNK_SEGMENT_SIZE - 1).getBlockTemplate()->getType() != blockType) {
							backDrawable = true;
						}
					}
				}

				if (Z < CHUNK_SEGMENT_SIZE - 1) {
					if (chunk->getBlock(X, Y, Z + 1).getBlockTemplate()->getType() != blockType) {
						frontDrawable = true;
					}
				}
				else {
					if (chunkExist[3]) {
						if (chunks[3]->getBlock(X, Y, 0).getBlockTemplate()->getType() != blockType) {
							frontDrawable = true;
						}
					}
				}

				if (upDrawable) {
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					vertexCount += 6;

					glm::vec2 texCoord = block.getBlockTemplate()->getUpTexCoords();
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y + Global::BLOCK_TEXTURE_SIZE);

					for (int counter = 0; counter < 6; counter++) {
						normals.emplace_back(glm::vec3(0, 1, 0));
					}
				}

				if (downDrawable) {
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					vertexCount += 6;

					glm::vec2 texCoord = block.getBlockTemplate()->getDownTexCoords();
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y + Global::BLOCK_TEXTURE_SIZE);

					for (int counter = 0; counter < 6; counter++) {
						normals.emplace_back(0, -1, 0);
					}
				}

				if (leftDrawable) {
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					vertexCount += 6;

					glm::vec2 texCoord = block.getBlockTemplate()->getLeftTexCoords();
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y);

					for (int counter = 0; counter < 6; counter++) {
						normals.emplace_back(glm::vec3(-1, 0, 0));
					}
				}

				if (rightDrawable) {
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					vertexCount += 6;

					glm::vec2 texCoord = block.getBlockTemplate()->getRightTexCoords();
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y);

					for (int counter = 0; counter < 6; counter++) {
						normals.emplace_back(glm::vec3(1, 0, 0));
					}
				}

				if (frontDrawable) {
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z + 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z + 0.5f));
					vertexCount += 6;

					glm::vec2 texCoord = block.getBlockTemplate()->getFrontTexCoords();
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x, texCoord.y);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y + Global::BLOCK_TEXTURE_SIZE);

					for (int counter = 0; counter < 6; counter++) {
						normals.emplace_back(glm::vec3(0, 0, 1));
					}
				}

				if (backDrawable) {
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X + 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y + 0.5f, inWorldZ + (Z - 0.5f));
					positions.emplace_back(inWorldX + (X - 0.5f), Y - 0.5f, inWorldZ + (Z - 0.5f));
					vertexCount += 6;

					glm::vec2 texCoord = block.getBlockTemplate()->getBackTexCoords();

					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x, texCoord.y);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x, texCoord.y + Global::BLOCK_TEXTURE_SIZE);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y);
					texCoords.emplace_back(texCoord.x + Global::BLOCK_TEXTURE_SIZE, texCoord.y + Global::BLOCK_TEXTURE_SIZE);

					for (int counter = 0; counter < 6; counter++) {
						normals.emplace_back(glm::vec3(0, 0, -1));
					}
				}
			}
		}
	}

	std::cout << "Verteces in chunk: " << vertexCount << "\n";

	chunk->setVertexPositions(positions);
	chunk->setVertexNormals(normals);
	chunk->setVertexTexCoords(texCoords);
	chunk->setBlocksUpdated(false);
	chunk->setMeshUpdated(true);
}

void Game::World::Draw() {
	glm::vec3 pos = GeneralPlayerCamera->getPosition();
	int CameraX = pos.x / CHUNK_SEGMENT_SIZE;
	int CameraY = pos.z / CHUNK_SEGMENT_SIZE;

	WorldDrawShader.use();
	WorldDrawShader.setMat4(ProjectionSpaceInShader, GeneralPlayerCamera->getProjection());
	WorldDrawShader.setMat4(ViewSpaceInShader, GeneralPlayerCamera->getViewMatrix());
	Global::BlockAtlas.bind(0);
	WorldDrawShader.setInt(BlockAtlasInShader, 0);

	const Engine::Frustum& frustum = GeneralPlayerCamera->getFrustum();
	for (int X = CameraX - RenderDistance; X <= CameraX + RenderDistance; X++) {
		for (int Y = CameraY - RenderDistance; Y <= CameraY + RenderDistance; Y++) {
			if(Chunks.find({X, Y}) != Chunks.end()){
				Chunk* chunk = Chunks[{X, Y}];	
				bool intersect = false;
				for(int index = 0; index < chunk->getSegments().size(); index++){
					if(frustum.intersectSphere(
						glm::vec3(X * CHUNK_SEGMENT_SIZE, (CHUNK_SEGMENT_SIZE * index) + CHUNK_SEGMENT_SIZE / 2, Y * CHUNK_SEGMENT_SIZE),
						CHUNK_SEGMENT_SIZE * 2
					)){
						intersect = true;
						break;
					}
				}
				if(intersect){
					chunk->draw();
				}
			} else {
				Chunks[{X, Y}] = new Chunk;
			}
		} 
	}
}