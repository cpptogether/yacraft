#ifndef YACRAFT_MATH_GENERAL
#define YACRAFT_MATH_GENERAL

namespace Math {

	/**
	* @brief https://en.wikipedia.org/wiki/Bilinear_interpolation
	* @return Result of biliniar interpolation.
	**/
	float BilinearInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight,
		float xMin, float xMax,
		float zMin, float zMax,
		float x, float z);

};

#endif