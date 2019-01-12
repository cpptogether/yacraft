#include <glm/glm.hpp>
#include <vector>
#include "Cube.h"

Cube::Cube() {
	bind();

	std::vector<glm::vec3> pos{
		{-1.0, -1.0, -1.0},
		{ -1.0, -1.0, 1.0 },
		{ 1.0, -1.0, -1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, 1.0, -1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, 1.0, 1.0 }
	};

	std::vector<unsigned int> indices{
		0, 1, 2,
		1, 2, 3,

		4, 5, 6,
		5, 6, 7,

		0, 4, 6,
		4, 6, 2,

		6, 2, 3,
		6, 3, 7,

		5, 7, 3,
		1, 3, 7,

		4, 0, 1,
		4, 5, 1
	};

	setPositions(pos);

	setIndices(indices);

	unbind();
}