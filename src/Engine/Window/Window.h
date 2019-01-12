#ifndef YACRAFT_WINDOW
#define YACRAFT_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <functional>
#include <unordered_map>
#include <Utilities/Keys.h>

namespace Window {

	/**
	* @brief Binding info struct. Used for calling bindings.
	**/
	struct BindingInfo {
		std::vector<Keys> keys;

		std::function<void(void)> function;
	};

	namespace Private {
		static GLFWwindow * windowFrame;

		static std::unordered_map<std::string, BindingInfo> bindings;

		/**
		* @brief Helper method for IsKeyPressed/IsKeyReleased.
		* @param keyCode Key code... 
		* @param status GLFW_PRESS or GLFW_RELEASE for check
		**/
		bool keyCheck(int keyCode, int status);

		/**
		* @brief Helper method for IsMousePressed/IsMouseReleased.
		* @param keyCode Key code...
		* @param status GLFW_PRESS or GLFW_RELEASE for check
		**/
		bool mouseCheck(int mouseCode, int status);
	};

	/**
	* @brief Checking for key press
	* @param keyCode Key code for check
	* @return True if key is pressed, false if not
	**/
	bool IsKeyPressed(Keys keyCode);

	/**
	* @brief Checking for key release
	* @param keyCode Key code for check
	* @return True if key is released, false if not
	**/
	bool IsKeyReleased(Keys keyCode);

	/**
	* @brief Checking for mouse button press
	* @param mouseCode Mouse button code for check
	* @return True if mouse button is pressed, false if not
	**/
	bool IsMousePressed(Keys mouseCode);

	/**
	* @brief Checking for mouse button release
	* @param mouseCode Mouse button code for check
	* @return True if mouse button is released, false if not
	**/
	bool IsMouseReleased(Keys mouseCode);

	/**
	* @brief Window create.
	* @param width Width of window.
	* @param height Height of window.
	* @param title Title of window.
	**/
	void Create(unsigned int width, unsigned int height, const std::string & title);

	/**
	* @brief Window shows all what you drawn.
	**/
	void SwapBuffers();

	/**
	* @brief Checks if the window is open or not.
	* @return True if window is open, false if not
	**/
	bool IsOpen();

	/**
	* @brief Shows cursor.
	**/
	void EnableCursor();

	/**
	* @brief Hides cursor.
	**/
	void DisableCursor();

	/**
	* @brief Return cursor position.
	* @returns glm::vec2 Cursor position.
	**/
	glm::vec2 GetCursorPosition();

	/**
	* @brief Returns delta time (time for creating 1 frame)
	* @returns float Delta time
	**/
	float GetDeltaTime();

	/**
	* @brief Return the time that the program worked.
	* @returns float The time that the program worked.
	**/
	float GetTime();

	/**
	* @brief Returns size of the window.
	* @returns glm::vec2 Size of the window.
	**/
	glm::vec2 GetSize();

	/**
	* @brief Sets binding.
	* @param bindName Name of a binding.
	* @param keys Keys which need to press for run this binding
	* @param function Function to run when all keys pressed.
	**/
	void SetBinding(const std::string & bindName, std::vector<Keys> keys, std::function<void(void)> function);

	/**
	* @brief Runs all bindings.
	**/
	void RunBindings();

};

#endif
