#ifndef YACRAFT_GL_FRAMEBUFFER
#define YACRAFT_GL_FRAMEBUFFER

#include <glm/glm.hpp>
#include <Engine/OpenGL/Texture/Texture.h>

namespace GL {

	class Framebuffer {
	private:
		unsigned int FBO;

		unsigned int RBO;

		unsigned int width;

		unsigned int height;

		unsigned int texture;
	public:
		/**
		* @brief Equals to another framebuffer
		* @param buffer Another framebuffer.
		**/
		Framebuffer(const Framebuffer & buffer);

		/**
		* @brief Equals to another framebuffer
		* @param buffer Another framebuffer.
		**/
		void operator =(const Framebuffer & buffer);

		/**
		* @brief Framebuffer initialize
		* @param width Width of framebuffer
		* @param height Height of framebuffer
		**/
		void initialize(unsigned int width, unsigned int height);

		/**
		* @brief Bind this framebuffer.
		**/
		void bind() const;

		/**
		* @brief Returns the framebuffer texture.
		* @returns GL::Texture Texture.
		**/
		Texture getTexture() const;

		/**
		* @brief Clears color buffer for framebuffers.
		**/
		static void ClearColorBuffer();

		/**
		* @brief Clears depth buffer for framebuffers.
		**/
		static void ClearDepthBuffer();

		/**
		* @brief Enables depth test. 
		**/
		static void EnableDepthTest();

		/**
		* @brief Disables depth test.
		**/
		static void DisableDepthTest();

		/**
		* @brief Enables face culling.
		**/
		static void EnableFaceCulling();

		/**
		* @brief Disables face culling.
		**/
		static void DisableFaceCulling();

		/**
		* @brief Sets clear color for framebuffers.
		* @param color Color.
		**/
		static void SetClearColor(const glm::vec4 & color);

		/**
		* @brief Binds the default framebuffer.
		**/
		static void BindDefault();

		/**
		* @brief Makes screenshot.
		* @param width Width of binded framebuffer.
		* @param height Height of binded framebuffer.
		* @returns char* Return RGBA image.
		**/
		static char * ReadPixels(unsigned int width, unsigned int height);

	};

}

#endif
