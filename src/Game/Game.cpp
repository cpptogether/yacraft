#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Engine/APIHeader.h"
#include "Global.h"
#include "Block/BlockDefines.h"
#include "World/World.h"
#include "Game.h"
#include "DataTypes/BiArray.h"

void Game::Init() {
	Window::Create(800, 600, "YetAnotherCraft");
	Window::DisableCursor();

	Global::BlockAtlas = GL::LoadTexture("res/Textures/BlockAtlas.png");

	Engine::Camera camera;
	camera.updateProjection();
	camera.setSpeed(10.0f);

	Blocks::Init();

	World::GeneralPlayerCamera = &camera;
	World::Init();

	auto onMove = [&](){
		std::cout << camera.getPosition().x << " " << 
			camera.getPosition().y << " " << camera.getPosition().z << "\n";
		std::cout << (int)camera.getPosition().x / CHUNK_SEGMENT_SIZE << " " 
			<< (int)camera.getPosition().y / CHUNK_SEGMENT_SIZE << " "
			<< (int)camera.getPosition().z / CHUNK_SEGMENT_SIZE << "\n";
		std::cout << (int)camera.getPosition().x / CHUNK_SEGMENT_SIZE << " "
			<< (int)camera.getPosition().x % CHUNK_SEGMENT_SIZE << "\n";
		std::cout << (int)camera.getPosition().y / CHUNK_SEGMENT_SIZE << " "
			<< (int)camera.getPosition().y % CHUNK_SEGMENT_SIZE << "\n";
		std::cout << (int)camera.getPosition().z / CHUNK_SEGMENT_SIZE << " "
			<< (int)camera.getPosition().z % CHUNK_SEGMENT_SIZE << "\n";
	};

	Window::SetBinding("flyFront", { Keys::W }, [&]() {
		camera.processKeyboard(CameraDir::FORWARD,
			Window::GetDeltaTime());
		onMove();
	});

	Window::SetBinding("flyLeft", { Keys::A }, [&]() {
		camera.processKeyboard(CameraDir::LEFT, Window::GetDeltaTime());
		onMove();
	});

	Window::SetBinding("flyBack", { Keys::S }, [&]() {
		camera.processKeyboard(CameraDir::BACKWARD,
			Window::GetDeltaTime());
		onMove();
	});

	Window::SetBinding("flyRight", { Keys::D }, [&]() {
		camera.processKeyboard(CameraDir::RIGHT,
			Window::GetDeltaTime());
		onMove();
	});

	Window::SetBinding("flyUp", { Keys::SPACE }, [&]() {
		camera.processKeyboard(CameraDir::UP,
			Window::GetDeltaTime());
		onMove();
	});

	Window::SetBinding("flyDown", { Keys::LEFT_CONTROL }, [&]() {
		camera.processKeyboard(CameraDir::DOWN,
			Window::GetDeltaTime());
		onMove();
	});

	Window::SetBinding("flyFaster", { Keys::LEFT_SHIFT }, [&](){
		camera.setSpeed(camera.getSpeed() * 1.1f);
	});

	Window::SetBinding("flySlower", { Keys::LEFT_ALT }, [&](){
		if(camera.getSpeed() > 0.1f){
			camera.setSpeed(camera.getSpeed() * 0.9f + 0.001f);
		}
	});

	Window::SetBinding("showFPS", { Keys::R }, [&](){
		const glm::vec3& dir = camera.getFront();
		std::cout << "FPS: " << 1.0f / Window::GetDeltaTime() << "\n"
				<< "Front: " << dir.x << " " << dir.y << " " << dir.z << "\n";
	});

        /*Window::SetBinding("destroyBlocks", { Keys::MOUSE_BUTTON_LEFT }, [&](){
		glm::vec3 cameraPos = camera.getPosition();
		for(int X = cameraPos.x - 2; X <= cameraPos.x + 2; X++){
			for(int Y = cameraPos.y - 2; Y <= cameraPos.y + 2; Y++){
				for(int Z = cameraPos.z - 2; Z <= cameraPos.z + 2; Z++){
					if(Y >= 0){
						World::SetBlock(X, Y, Z, Blocks::Grass);
					}
				}
			}
		}
		World::Update();
	});*/

	GL::Framebuffer::EnableDepthTest();
	GL::Framebuffer::DisableFaceCulling();
	GL::Framebuffer::SetClearColor({ 0.1f, 0.2f, 0.5f, 1.0f });

	while (Window::IsOpen()) {
		GL::Framebuffer::ClearColorBuffer();
		GL::Framebuffer::ClearDepthBuffer();

		glm::vec2 cursorPos = Window::GetCursorPosition();
		camera.processMouseMovement(cursorPos.x, cursorPos.y);

		World::Draw();

		Window::SwapBuffers();
		Window::RunBindings();
	}
}
