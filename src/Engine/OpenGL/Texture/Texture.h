#ifndef YACRAFT_GL_TEXTURE
#define YACRAFT_GL_TEXTURE

#include <string>
#include <glm/glm.hpp>

namespace GL {

	/**
	* @brief Contains texture.
	**/
	class Texture {
	private:
		unsigned int ID = 0;

		int activeUnit = 0;

		std::string type;

		std::string path;

		glm::vec2 size;

	public:

		/**
		* @brief Setting the ID straight.
		**/
		Texture(unsigned int ID, unsigned int width, unsigned int height);

		Texture(const Texture& texture);

		void operator=(const Texture& texture);

		Texture();

		/**
		* @brief Getting the path of this texture.
		* @return std::string String with the path of this texture.
		**/
		const std::string & getPath() const;

		/**
		* @brief Getting the type of this texture.
		* @return std::string Type.
		**/
		const std::string & getType() const;

		/**
		* @brief Setting the type of this texture.
		**/
		void setType(const std::string & type);

		/**
		* @brief Getting the ID of this texture.
		* @returns unsigned int The ID of this texture.
		**/
		const unsigned int getID() const;

		/**
		* @brief Getting the size of this texture.
		* @returns glm::vec2 The size of this texture.
		**/
		const glm::vec2& getSize() const;

		/**
		* @brief Setting the active unit of this texture.
		**/
		void setActiveUnit(int activeUnit);

		/**
		* @brief Setting the active unit of this texture. Const version.
		**/
		void setActiveUnit(int activeUnit) const;

		/**
		* @brief Getting the active unit.
		* @returns int Active unit.
		**/
		int getActiveUnit() const;

		/**
		* @brief Binds this texture.
		**/
		void bind() const;

		/**
		* @brief Binds this texture and sets the active unit.
		* @param unit Active unit number to set.
		**/
		void bind(int unit) const;

		/**
		* @brief Binds this texture and sets the active unit.
		* @param unit Active unit number to set.
		**/
		void bind(int unit);

		/**
		* @brief Deletes this texture and releases resources.
		**/
		void release();

	};

}

#endif
