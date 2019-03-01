#ifndef YACRAFT_ENGINE_GL_PLATE
#define YACRAFT_ENGINE_GL_PLATE

#include <glm/glm.hpp>

#include "Shape.h"
#include "Engine/OpenGL/Buffer/ModelBuffer.h"

namespace GL{

	class Plate : public Shape {
	private:
		glm::vec3 verteces[4];
	public:
		void setVertexPosition(int index, const glm::vec3& position);

		void addToModelBuffer(ModelBuffer& buffer) const;
	};

};

#endif