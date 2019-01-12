#ifndef YACRAFT_GL_TYPES
#define YACRAFT_GL_TYPES

#include <Engine/Window/Window.h>

namespace GL {

	namespace Types {

		/*
		* @brief Enum of OpenGL GPU data types.
		*/
		enum GLTypes : const int {
			DOUBLE = GL_DOUBLE,
			FLOAT = GL_FLOAT,
			INT = GL_INT,
			UINT = GL_UNSIGNED_INT,
			SHORT = GL_SHORT,
			USHORT = GL_UNSIGNED_SHORT,
			BYTE = GL_BYTE,
			UBYTE = GL_UNSIGNED_BYTE
		};

	};

};


#endif