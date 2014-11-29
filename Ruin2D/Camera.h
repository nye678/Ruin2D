#ifndef __RUIN2D_CAMERA_H_
#define __RUIN2D_CAMERA_H_

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "WindowManager.h"

namespace Ruin2D
{
	class Camera
	{
	private:
		bool _dirty;
		glm::vec2 _position;
		float _zoom;
		glm::mat4 _camera;
		glm::mat4 _proj;

	public:
		glm::vec2 Position() const;

		void SetPosition(const glm::vec2 &);

		void SetCenterPosition(const glm::vec2 &);

		void Move(const glm::vec2 &);

		void Move(float x, float y);

		void UpdateCameraView(GLint cameraLocation);

		glm::ivec4 GetViewRectangle() const;

		Camera();
		Camera(const Camera &) = delete;
		Camera &operator= (const Camera &) = delete;
	};
}

#endif