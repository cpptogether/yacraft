#ifndef YACRAFT_GL_TEXTURE_LOADER
#define YACRAFT_GL_TEXTURE_LOADER

#include <string>
#include <vector>
#include "Texture.h"
#include "Cubemap.h"

namespace GL {

	/**
	* @brief Used for loading a texture from image.
	* @param path Path to the image.
	* @param reverse To reverse image or not.
	* @returns GL::Texture Loaded texture.
	**/
	Texture LoadTexture(const std::string& path, bool reverse = false);

	/**
	* @brief Used for loading a cubemap from image.
	* @param faces Paths to images.
	**/
	Cubemap LoadCubemap(const std::vector<std::string>& faces);

};

#endif 
