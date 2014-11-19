#ifndef __RUIN2D_CAMERA_H_
#define __RUIN2D_CAMERA_H_

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Singleton.h"
#include "WindowManager.h"

namespace Ruin2D
{
	class Camera
	{
		friend class Singleton<Camera>;

	private:
		static Singleton<Camera> Singleton;

		bool _dirty;
		glm::vec2 _position;
		float _zoom;
		glm::mat4 _camera;
		glm::mat4 _proj;

	public:
		static std::shared_ptr<Camera> Create();

		inline static std::shared_ptr<Camera> Get()
		{
			return Singleton.Get();
		}

		glm::vec2 Position() const;

		void SetPosition(const glm::vec2 &);

		void Move(const glm::vec2 &);

		void Move(float x, float y);

		void UpdateCameraView(GLint cameraLocation);

		glm::ivec4 GetViewRectangle() const;

	private:
		Camera();
		Camera(const Camera &) = delete;
		Camera &operator= (const Camera &) = delete;
	};
}

#endif