#ifndef YACRAFT_GL_MODELBUFFER
#define YACRAFT_GL_MODELBUFFER

#include <glm/glm.hpp>
#include <vector>
#include <Engine/OpenGL/Types.h>
#include "Buffer.h"

namespace GL {

	/**
	* @brief Modelbuffer which extends Buffer. Abstraction to easier creation models.
	**/
	class ModelBuffer : public Buffer {
	private:
		int vertexCount = 0;

	public:
		/**
		* @brief Initializes and creates 4 VBOs.
		**/
		ModelBuffer();

		void operator=(const ModelBuffer& buffer) {
			vertexCount = buffer.vertexCount;
		}

		/**
		* @brief Sets vertex positions.
		* @param glData Positions.
		**/
		void setPositions(std::vector<glm::vec3>& glData);

		/**
		* @brief Sets verteces normals.
		* @param glData Normals.
		**/
		void setNormals(std::vector<glm::vec3>& glData);

		/**
		* @brief Sets verteces texture coordinats.
		* @param glData Tex.Coords.
		**/
		void setTexCoords(std::vector<glm::vec2>& glData);

		/**
		* @brief Sets verteces tangents.
		* @param glData Tangents.
		**/
		void setTangents(std::vector<glm::vec3>& glData);

		/**
		* @brief Sets sequence to draw verteces.
		* @param indices Indices.
		**/
		void setIndices(std::vector<unsigned int>& indices);

		/**
		* @brief Draw verteces as array.
		**/
		void drawArrays();
	};

};

#endif
