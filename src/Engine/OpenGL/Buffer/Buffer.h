#ifndef YACRAFT_GL_BUFFER
#define YACRAFT_GL_BUFFER

#include <vector>

namespace GL {

	/**
	* @brief Class for easier manipulating OpenGL buffers.
	**/
	class Buffer {

	private:

		unsigned int EBO;

		std::vector<unsigned int> VBOs;

		int sequenceCount = 0;

		unsigned int VAO;

	public:
		/**
		* @brief Initializing of buffer.
		**/
		Buffer();

		void operator=(const Buffer& buffer);

		void createIndeces();

		/**
		* @brief Binds this buffer.
		**/
		void bind() const;

		/**
		* @brief Unbinds this buffer.
		**/
		void unbind() const;

		/**
		* @brief Creates more VBOs.
		* @param count How many VBOs to create.
		**/
		void create(int count = 1);

		/**
		* @brief Sets data to VBOs[index].
		* @tparam Type Data type.
		* @param index Index of VBO in VBOs list of this buffer.
		* @param data Data to set.
		* @param count Amount of data.
		**/
		template<class Type>
		void setData(int index, void * data, int count) {
			glBindBuffer(GL_ARRAY_BUFFER, VBOs.at(index));
			glBufferData(GL_ARRAY_BUFFER, sizeof(Type) * count, data,
				GL_STATIC_DRAW);
		}

		/**
		* @brief Adds data to begin of VBOs[index].
		* @tparam Type Data type.
		* @param index Index of VBO in VBOs list of this buffer.
		* @param data Data to set.
		* @param count Amount of data.
		**/
		template<class Type>
		void addData(int index, void * data, int count) {
			glBindBuffer(GL_ARRAY_BUFFER, VBOs.at(index));
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Type) * count, data);
		}

		/**
		* @brief Sets sequence(indeces) to run verteces.
		* @param sequence Sequence.
		* @param count Count of indices.
		**/
		void setSequence(void * sequence, int count);

		/**
		* @brief Adds sequence (indeces) to run verteces.
		* @param sequence Sequence.
		* @param count Count of indices.
		**/
		void addSequence(void * sequence, int count) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * count,
				sequence);
			this->sequenceCount = count;
		}
		
		/**
		* @brief Enables location.
		* @param index Location index.
		**/
		void enableAttribute(int index);

		/**
		* @brief Disables location.
		* @param index Location index.
		**/
		void disableAttribute(int index);

		/**
		* @brief Sets data to VBOs[index].
		* @tparam Type Data type.
		* @tparam TypeOnGPU OpenGL's type on GPU.
		* @param index Index of VBO in VBOs list of this buffer.
		* @param size Count of TypeOnGPU.
		* @param pointer Offset.
		**/
		template<class Type, const int TypeOnGPU>
		void setAttribute(unsigned int index, unsigned int size = 1, int pointer = 0) {
			glBindBuffer(GL_ARRAY_BUFFER, VBOs.at(index));
			glVertexAttribPointer(index, size, TypeOnGPU, false, sizeof(Type),
				(void*)pointer);
		}

		/**
		* @brief Draw as elemented array of verteces.
		**/
		void draw() const;

		/**
		* @brief Draw as array of verteces.
		**/
		void drawArray() const;

		/**
		* @brief Deletes this buffer.
		**/
		void release();

	};

}
#endif
