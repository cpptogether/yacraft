#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "Window.h"

namespace Window {

	struct {
		float time;

		float lastTime;

		void calculate(float currentTime) {
			time = currentTime - lastTime;
			lastTime = currentTime;
		}
	} Delta;


	namespace Private {
		bool keyCheck(int keyCode, int status) {
			if (glfwGetKey(windowFrame, (int)keyCode) == status) {
				return true;
			}
			return false;
		}

		bool mouseCheck(int mouseCode, int status) {
			if (glfwGetMouseButton(windowFrame, (int)mouseCode) == status) {
				return true;
			}
			return false;
		}

		void runBinding(const BindingInfo & info) {
			bool isPressed = false;
			for (auto key : info.keys) {
				if (!(IsKeyPressed(key) || IsMousePressed(key))) {
					isPressed = true;
				}
			}
			if (!isPressed) {
				info.function();
			}
		}
	};

};

bool Window::IsKeyPressed(Keys keyCode) { return Private::keyCheck((int)keyCode, GLFW_PRESS); }

bool Window::IsKeyReleased(Keys keyCode) { return Private::keyCheck((int)keyCode, GLFW_RELEASE); }

bool Window::IsMousePressed(Keys mouseCode) {
	return Private::mouseCheck((int)mouseCode, GLFW_PRESS);
}

bool Window::IsMouseReleased(Keys mouseCode) {
	return Private::mouseCheck((int)mouseCode, GLFW_RELEASE);
}

void Window::Create(unsigned int width, unsigned int height, const std::string & title) {
	if (!glfwInit()) {
		std::cerr << "GLFW initialize error.\n";
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Private::windowFrame =
		glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!Private::windowFrame) {
		std::cerr << Private::windowFrame << "\n"
			<< title << " window creating error.\n";
		exit(-1);
	}

	glfwMakeContextCurrent(Private::windowFrame);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << title << " window OpenGL context creating failed\n";
		exit(-1);
	}

	glfwShowWindow(Private::windowFrame);
}

void Window::SwapBuffers() {
	Delta.calculate(glfwGetTime());
	glfwSwapBuffers(Private::windowFrame);
	glfwPollEvents();
}

bool Window::IsOpen() { return !glfwWindowShouldClose(Private::windowFrame); }

void Window::EnableCursor() {
	glfwSetInputMode(Private::windowFrame, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::DisableCursor() {
	glfwSetInputMode(Private::windowFrame, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

glm::vec2 Window::GetCursorPosition() {
	double X, Y;
	glfwGetCursorPos(Private::windowFrame, &X, &Y);
	return glm::vec2(X, Y);
}

float Window::GetDeltaTime() { return Delta.time; }

float Window::GetTime() { return (float)glfwGetTime(); }

glm::vec2 Window::GetSize() {
	glm::vec2 size;
	glfwGetWindowSize(Private::windowFrame, (int*)&size.x, (int*)&size.y);
	return size;
}

void Window::SetBinding(const std::string & bindName, std::vector<Keys> keys, std::function<void(void)> function) {
	BindingInfo bind;
	bind.keys = keys;
	bind.function = function;
	Private::bindings[bindName] = bind;
}

void Window::RunBindings() {
	for (auto& binding : Private::bindings) {
		Private::runBinding(binding.second);
	}
}