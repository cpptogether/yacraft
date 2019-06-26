cmake_minimum_required (VERSION 3.8)
  
project(YaCraft) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  
#add_subdirectory(thirdParty/p7)
add_subdirectory(thirdParty/glfw)
add_subdirectory(thirdParty/glm)

find_package(OpenGL REQUIRED)
 
add_executable( 
	YaCraftExec 
	thirdParty/glad/src/glad.c
	src/Utilities/Utilities.cpp
	src/Math/General.cpp 
	src/Math/FastNoise.cpp
	src/Engine/Window/Window.cpp
        src/Engine/Frustum/Frustum.cpp
	src/Engine/Camera/Camera.cpp
	src/Engine/OpenGL/Buffer/Buffer.cpp
	src/Engine/OpenGL/Buffer/ModelBuffer.cpp
	src/Engine/OpenGL/Shader/Shader.cpp
	src/Engine/OpenGL/Texture/Texture.cpp 
	src/Engine/OpenGL/Texture/TextureLoader.cpp
	src/Engine/OpenGL/Framebuffer/Framebuffer.cpp 
	src/Game/Global.cpp
	src/Game/Block/BlockTemplate.cpp
	src/Game/Block/BlockDefines.cpp
	src/Game/Block/Block.cpp
	src/Game/World/ChunkSegment.cpp
	src/Game/World/Chunk.cpp
	src/Game/World/World.cpp
	src/Game/Primitive/Cube.cpp
	src/Game/Game.cpp
	YaCraft.cpp  
)

target_include_directories(
	YaCraftExec  
	PUBLIC thirdParty/glfw/include 
	PUBLIC thirdParty/glad/include  
	PUBLIC thirdParty/glm
	PUBLIC thirdParty/stb
	#PUBLIC thirdParty/p7/headers
	PUBLIC src
)

target_compile_options(
	YaCraftExec 
	PUBLIC -O0
	PUBLIC -g
)

target_link_libraries(
	YaCraftExec 
	glfw
	#P7
)  

if(${OPENGL_FOUND})
	target_include_directories(YaCraftExec PUBLIC ${OPENGL_INCLUDE_DIR})
	target_link_libraries(YaCraftExec ${OPENGL_gl_LIBRARY})
endif()

 
