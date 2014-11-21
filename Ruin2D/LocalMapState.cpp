#include "LocalMapState.h"

using namespace Ruin2D;
using namespace Ruin2DGame;

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
	double speed = 2.0;
	if (up)
	{
		moveVec.y = -speed;
		AllData::PlayerSprite.SetDirection(1);
	}

	if (left)
	{
		moveVec.x = -speed;
		AllData::PlayerSprite.SetDirection(2);
	}

	if (down)
	{
		moveVec.y = speed;
		AllData::PlayerSprite.SetDirection(0);
	}

	if (right)
	{
		moveVec.x = speed;
		AllData::PlayerSprite.SetDirection(3);
	}

	if (up || left || down || right)
	{
		AllData::PlayerSprite.StepFrame(deltaTime);
	}

	//camera->Move(moveVec);
	AllData::PlayerPos += moveVec;
	camera->SetCenterPosition(AllData::PlayerPos);
}

void LocalMapState::Render()
{
	if (_data != nullptr)
	{
		auto camera = Camera::Get();
		auto graphics = Graphics::Get();

		auto cameraViewRect = camera->GetViewRectangle();

		_data->tileMap.DrawBackgroundLayers(_data->tileSet, cameraViewRect);

		AllData::PlayerSprite.DrawSprite(AllData::PlayerPos);

		_data->tileMap.DrawForegroundLayers(_data->tileSet, cameraViewRect);
	}
}