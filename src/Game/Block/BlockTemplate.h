#ifndef YACRAFT_GAME_BLOCK_TEMPLATE
#define YACRAFT_GAME_BLOCK_TEMPLATE

#include <glm/glm.hpp>
#include <string>

namespace Game {

	/**
	* @brief Block template. Containts a texture data and other info.
	**/
	class BlockTemplate {
	private:
		glm::vec2 backTexCoord;
		glm::vec2 frontTexCoord;
		glm::vec2 leftTexCoord;
		glm::vec2 rightTexCoord;
		glm::vec2 bottomTexCoord;
		glm::vec2 topTexCoord;
		int type = 0;
		std::string name;
	public:

		bool operator==(const BlockTemplate& blockTemplate);

		void setName(const std::string& string);

		const std::string& getName();

		/**
		* @brief Sets backTexCoord to texCoord
		* @param texCoord Texture coordinate in pixels.
		**/
		void setBackTexCoords(const glm::vec2& texCoord);

		/**
		* @brief Returns back tex coords.
		* @return glm::vec2 Back tex coords.
		**/
		const glm::vec2& getBackTexCoords() const;

		/**
		* @brief Sets frontTexCoord to texCoord
		* @param texCoord Texture coordinate in pixels.
		**/
		void setFrontTexCoords(const glm::vec2& texCoord);

		/**
		* @brief Returns front tex coords.
		* @return glm::vec2 Front tex coords.
		**/
		const glm::vec2& getFrontTexCoords() const;

		/**
		* @brief Sets leftTexCoord to texCoord
		* @param texCoord Texture coordinate in pixels.
		**/
		void setLeftTexCoords(const glm::vec2& texCoord);

		/**
		* @brief Returns left tex coords.
		* @return glm::vec2 Left tex coords.
		**/
		const glm::vec2& getLeftTexCoords() const;

		/**
		* @brief Sets rightTexCoord to texCoord
		* @param texCoord Texture coordinate in pixels.
		**/
		void setRightTexCoords(const glm::vec2& texCoord);

		/**
		* @brief Returns right tex coords.
		* @return glm::vec2 Right tex coords.
		**/
		const glm::vec2& getRightTexCoords() const;

		/**
		* @brief Sets bottomTexCoord to texCoord
		* @param texCoord Texture coordinate in pixels.
		**/
		void setDownTexCoords(const glm::vec2& texCoord);

		/**
		* @brief Returns bottom tex coords.
		* @return glm::vec2 Bottom tex coords.
		**/
		const glm::vec2& getDownTexCoords() const;

		/**
		* @brief Sets topTexCoord to texCoord
		* @param texCoord Texture coordinate in pixels.
		**/
		void setUpTexCoords(const glm::vec2& texCoord);

		/**
		* @brief Returns top tex coords.
		* @return glm::vec2 Top tex coords.
		**/
		const glm::vec2& getUpTexCoords() const;

		/**
		* @brief Sets type.
		* @param type Type.
		**/
		void setType(int type);

		/**
		* @brief Returns type.
		* @retuns Type.
		**/
		int getType() const;

	};

}

#endif