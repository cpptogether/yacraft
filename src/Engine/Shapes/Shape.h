#ifndef YACRAFT_ENGINE_GL_SHAPE
#define YACRAFT_ENGINE_GL_SHAPE

#include "Engine/OpenGL/Buffer/ModelBuffer.h"

namespace GL{

	class Shape{
	public:
		virtual void addToModelBuffer(ModelBuffer& buffer){}
	};

};

#endif