#include "Camera.h"

using namespace std;
using namespace glm;
using namespace Ruin2D;

Camera::Camera()
	: _position(vec2(0.0f, 0.0f)), _dirty(true), _zoom(2.0f)
{
	auto windowSize = WindowManager::Get()->GetSize();
	_proj = ortho(0.0f, (float)windowSize.x, (float)-windowSize.y, 0.0f);
	_camera = mat4(1.0);
}

shared_ptr<Camera> Camera::Create()
{
	return Singleton.Create();
}

vec2 Camera::Position() const
{
	return _position;
}

void Camera::SetPosition(const vec2 &position)
{
	_position = position;
	_dirty = true;
}

void Camera::Move(const vec2 &amount)
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
		_camera = glm::scale(mat4(1.0), vec3(_zoom, _zoom, 0.0f)) * glm::translate(mat4(1.0), vec3(_position, 0.0f));
		//auto cameraView = translate(_cameraView, vec3(_position, 0.0f));
		//cameraView = scale(cameraView, vec3(_zoom, _zoom, 0.0f));
		auto cameraView = _proj * _camera;
		glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, value_ptr(cameraView));

		_dirty = false;
	}
}

ivec4 Camera::GetViewRectangle() const
{
	// HACK!
	return ivec4(_position.x, _position.y, 1024 / _zoom, 768 / _zoom);
}