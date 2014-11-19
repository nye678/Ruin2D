#ifndef __RUIN2D_OBJECT_BUFFER_H_
#define __RUIN2D_OBJECT_BUFFER_H_

#include <GL3\gl3w.h>
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace Ruin2D
{
	enum ObjectType
	{
		Static, Dynamic
	};

	struct ObjectBufferData
	{
		ObjectType type;
		size_t offset;
		size_t size;
	};

	class ObjectBuffer
	{
	private:
		GLuint _handle;
		size_t _size;

	public:
		ObjectBuffer(size_t size);
	};
}

#endif