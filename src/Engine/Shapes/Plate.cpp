#include "Plate.h"

void GL::Plate::setVertexPosition(int index, const glm::vec3& position){
	verteces[index] = position;
}

void GL::Plate::addToModelBuffer(GL::ModelBuffer& buffer) const{
	buffer.bind();

	std::vector<glm::vec3> pos = {
		verteces[0],
		verteces[1],
		verteces[2],
		verteces[1],
		verteces[2],
		verteces[3]
	};

	std::vector<glm::vec2> texCoord = {
		{0.0f, 1.0f},
		{1.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 0.0f}
	};

	buffer.addPositions(pos);
	buffer.addTexCoords(texCoord);

	buffer.unbind();
}