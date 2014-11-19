#include "LocalMapState.h"

using namespace Ruin2D;

LocalMapState::LocalMapState(LocalMapData* data)
	: GameState(StateType::Local), _data(data)
{}

bool up, down, left, right;

void LocalMapState::Update(double deltaTime)
{
	auto input = InputManager::Get();
	auto events = input->GetEvents();

	for (auto inputEvent : events)
	{
		if (inputEvent.key == GLFW_KEY_W)
		{
			if (inputEvent.action == GLFW_PRESS)
				up = true;
			else if (inputEvent.action == GLFW_RELEASE)
				up = false;
		}

		if (inputEvent.key == GLFW_KEY_A)
		{
			if (inputEvent.action == GLFW_PRESS)
				left = true;
			else if (inputEvent.action == GLFW_RELEASE)
				left = false;
		}

		if (inputEvent.key == GLFW_KEY_S)
		{
			if (inputEvent.action == GLFW_PRESS)
				down = true;
			else if (inputEvent.action == GLFW_RELEASE)
				down = false;
		}

		if (inputEvent.key == GLFW_KEY_D)
		{
			if (inputEvent.action == GLFW_PRESS)
				right = true;
			else if (inputEvent.action == GLFW_RELEASE)
				right = false;
		}
	}

	auto camera = Camera::Get();
	auto moveVec = glm::vec2(0.0, 0.0);
	double speed = 5.0;
	if (up)
	{
		moveVec.y = -speed;
	}

	if (left)
	{
		moveVec.x = speed;
	}

	if (down)
	{
		moveVec.y = speed;
	}

	if (right)
	{
		moveVec.x = -speed;
	}

	camera->Move(moveVec);
}

void LocalMapState::Render()
{
	if (_data != nullptr)
	{
		auto camera = Camera::Get();
		auto graphics = Graphics::Get();

		auto cameraViewRect = camera->GetViewRectangle();

		_data->tileMap.DrawBackgroundLayers(_data->tileSet, cameraViewRect);

		// Draw sprite layers.

		_data->tileMap.DrawForegroundLayers(_data->tileSet, cameraViewRect);
	}
}