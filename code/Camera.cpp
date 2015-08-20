#include "Camera.h"

using namespace std;
using namespace Ruin2D;

Camera::Camera()
	: _position(glm::vec2(0.0f, 0.0f)), _dirty(true), _zoom(2.0f)
{
	// Hack window size
	//_proj = glm::ortho(0.0f, (float)1024, (float)-768, 0.0f, 0.1f, 10000.0f);
	_proj = glm::ortho(0.0f, 1024.0f, -768.0f, 0.0f);
	_camera = glm::mat4(1.0);
}

glm::vec2 Camera::Position() const
{
	return _position;
}

void Camera::SetPosition(const glm::vec2 &position)
{
	_position = position;
	_dirty = true;
}

void Camera::SetCenterPosition(const glm::vec2 &position)
{
	_position.x = -position.x;
	_position.y = position.y;
	// Hack window size
	_position.x += 1024.0f / (2.0f * _zoom);
	_position.y -= 768.0f / (2.0f * _zoom);
	_dirty = true;

}

void Camera::Move(const glm::vec2 &amount)
{
	_position += amount;
	_dirty = true;
}

void Camera::Move(float x, float y)
{
	_position.x += x;
	_position.y += y;
	_dirty = true;
}

void Camera::UpdateCameraView(GLint cameraLocation)
{
	if (_dirty)
	{
		_camera = glm::scale(glm::mat4(1.0), glm::vec3(_zoom, _zoom, 0.0f)) * glm::translate(glm::mat4(1.0), glm::vec3(_position, 0.0f));
		//_camera = glm::mat4(1.0f);
		//auto cameraView = translate(_cameraView, vec3(_position, 0.0f));
		//cameraView = scale(cameraView, vec3(_zoom, _zoom, 0.0f));
		auto cameraView = _proj * _camera;
		glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, glm::value_ptr(cameraView));

		_dirty = false;
	}
}

glm::ivec4 Camera::GetViewRectangle() const
{
	// HACK!
	return glm::ivec4(_position.x, _position.y, 1024 / _zoom, 768 / _zoom);
}