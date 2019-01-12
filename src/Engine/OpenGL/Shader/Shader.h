#ifndef YACRAFT_GL_SHADER
#define YACRAFT_GL_SHADER

#include <string>
#include <glm/glm.hpp>
#include <Engine/Window/Window.h>

namespace GL {

	/**
	* @brief Class for manipulating shaders.
	**/
	class Shader {
	private:
		std::string vertexCode;

		std::string fragmentCode;

		unsigned int ID;

		/**
		* @brief Checks for compile errors.
		* @param shader Shader ID.
		* @param type Shader type.
		**/
		void checkCompileErrors(GLuint shader, const std::string & type) const;


	public:
		Shader() {}

		Shader(const Shader & shader);

		void operator =(const Shader & shader);

		/**
		* @brief Sets shaders path and compiles.
		* @param vertexShaderPath Vertex shader path.
		* @param fragmentShaderPath Fragment shader path.
		**/
		Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath);

		/**
		* @brief Sets vertex shader path.
		* @param path Path of a vertex shader.
		**/
		void setVertex(const std::string & path);

		/**
		* @brief Sets fragment shader path.
		* @param path Path of a fragment shader.
		**/
		void setFragment(const std::string & path);

		/**
		* @brief Compiles shader.
		**/
		void compile();

		/**
		* @brief Binds this shader.
		**/
		void use() const;

		/**
		* @brief Returns uniform location of varName.
		* @param varName Variable to find and return uniform location.
		**/
		unsigned int getUniformPosition(const std::string & varName) const;
	
		/**
		* @brief Sets bool in name
		* @param name Uniform variable name.
		* @param value Value to set.
		**/
		void setBool(const std::string & name, bool value) const;

		/**
		* @brief Sets bool in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param value Value to set.
		**/
		void setBool(unsigned int uniformLocation, bool value) const;

		/**
		* @brief Sets int in name
		* @param name Uniform variable name.
		* @param value Value to set.
		**/
		void setInt(const std::string & name, int value) const;

		/**
		* @brief Sets int in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param value Value to set.
		**/
		void setInt(unsigned int uniformLocation, int value) const;

		/**
		* @brief Sets float in name
		* @param name Uniform variable name.
		* @param value Value to set.
		**/
		void setFloat(const std::string & name, float value) const;

		/**
		* @brief Sets float in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param value Value to set.
		**/
		void setFloat(unsigned int uniformLocation, float value) const;

		/**
		* @brief Sets glm::vec2 in name
		* @param name Uniform variable name.
		* @param value Value to set.
		**/
		void setVec2(const std::string & name, const glm::vec2 & value) const;

		/**
		* @brief Sets glm::vec2 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param value Value to set.
		**/
		void setVec2(unsigned int uniformLocation, const glm::vec2 & value) const;

		/**
		* @brief Sets glm::vec2 in name
		* @param name Uniform variable name.
		* @param x X 
		* @param y Y
		**/
		void setVec2(const std::string & name, float x, float y) const;

		/**
		* @brief Sets glm::vec2 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param x X
		* @param y Y
		**/
		void setVec2(unsigned int uniformLocation, float x, float y) const;

		/**
		* @brief Sets glm::vec3 in name
		* @param name Uniform variable name.
		* @param value Value to set.
		**/
		void setVec3(const std::string & name, const glm::vec3 & value) const;

		/**
		* @brief Sets glm::vec3 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param value Value to set.
		**/
		void setVec3(unsigned int uniformLocation, const glm::vec3 & value) const;

		/**
		* @brief Sets glm::vec3 in name
		* @param name Uniform variable name.
		* @param x X
		* @param y Y 
		* @param z Z
		**/
		void setVec3(const std::string & name, float x, float y, float z) const;

		/**
		* @brief Sets glm::vec3 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param x X
		* @param y Y
		* @param z Z
		**/
		void setVec3(unsigned int uniformLocation, float x, float y, float z) const;

		/**
		* @brief Sets glm::vec4 in name
		* @param name Uniform variable name.
		* @param value Value to set.
		**/
		void setVec4(const std::string & name, const glm::vec4 & value) const;

		/**
		* @brief Sets glm::vec4 in name
		* @param name Uniform variable name.
		* @param x X
		* @param y Y
		* @param z Z
		* @param w W 
		**/
		void setVec4(const std::string & name, float x, float y, float z, float w) const;

		/**
		* @brief Sets glm::vec4 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param value Value to set.
		**/
		void setVec4(unsigned int uniformLocation, const glm::vec4 & value) const;

		/**
		* @brief Sets glm::vec4 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param x X
		* @param y Y
		* @param z Z
		* @param w W
		**/
		void setVec4(unsigned int uniformLocation, float x, float y, float z, float w) const;

		/**
		* @brief Sets glm::mat2 in name
		* @param name Uniform variable name.
		* @param mat Value to set.
		**/
		void setMat2(const std::string & name, const glm::mat2 & mat) const;

		/**
		* @brief Sets glm::mat2 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param mat Value to set.
		**/
		void setMat2(unsigned int uniformLocation, const glm::mat2 & mat) const;

		/**
		* @brief Sets glm::mat3 in name
		* @param name Uniform variable name.
		* @param mat Value to set.
		**/
		void setMat3(const std::string & name, const glm::mat3 & mat) const;

		/**
		* @brief Sets glm::mat3 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param mat Value to set.
		**/
		void setMat3(unsigned int uniformLocation, const glm::mat3 & mat) const;

		/**
		* @brief Sets glm::mat4 in name
		* @param name Uniform variable name.
		* @param mat Value to set.
		**/
		void setMat4(const std::string & name, const glm::mat4 & mat) const;

		/**
		* @brief Sets glm::mat4 in uniformLocation
		* @param uniformLocation Uniform location of variable.
		* @param mat Value to set.
		**/
		void setMat4(unsigned int uniformLocation, const glm::mat4 & mat) const;

	};

}
#endif
