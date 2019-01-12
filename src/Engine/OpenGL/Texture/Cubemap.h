#ifndef YACRAFT_GL_CUBEMAP
#define YACRAFT_GL_CUBEMAP

#include "Texture.h"

namespace GL {
	
	/**
	* @brief Cubemap. 6 textures. Wrapper of texture and no more.
	**/
	class Cubemap : public Texture {
	public:
		Cubemap(unsigned int ID) : Texture(ID, 0, 0) {}
	};

}

#endif
