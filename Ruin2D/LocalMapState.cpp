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

		if (inputEvent.key == GLFW_KEY_UP && inputEvent.action == GLFW_RELEASE)
		{
			AllData::PlayerLayer += 1;
		}

		if (inputEvent.key == GLFW_KEY_DOWN && inputEvent.action == GLFW_RELEASE)
		{
			AllData::PlayerLayer = glm::max(AllData::PlayerLayer - 1, 0);
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
	auto pos = AllData::PlayerPos + moveVec;
	auto gridLoc = _data->tileMap.WorldToGrid(pos.x, pos.y);
	auto tileIndex = _data->tileMap.GetTile(gridLoc.y, gridLoc.x, AllData::PlayerLayer-1);
	auto tileProps = _data->tileSet.GetTileProperties(tileIndex);

	if (!tileProps.blocking)
	{
		AllData::PlayerPos += moveVec;
		camera->SetCenterPosition(AllData::PlayerPos);

		/*bool isStairsTile = _data->tileMap.IsStairTile(gridLoc.y, gridLoc.x, AllData::PlayerLayer);
		if (isStairsTile && !AllData::PlayerOnStairs)
		{
			AllData::PlayerOnStairs = true;
			AllData::PlayerLayer += 1;
		}

		bool lowerStairs = _data->tileMap.IsStairTile(gridLoc.y, gridLoc.x, AllData::PlayerLayer - 1);
		if (lowerStairs && !AllData::PlayerOnStairs)
		{
			AllData::PlayerOnStairs = true;
			AllData::PlayerLayer -= 1;
		}

		if (!isStairsTile && !lowerStairs && AllData::PlayerOnStairs)
		{
			AllData::PlayerOnStairs = false;
		}*/

		
	}
}

void LocalMapState::Render()
{
	if (_data != nullptr)
	{
		auto camera = Camera::Get();
		auto graphics = Graphics::Get();

		auto cameraViewRect = camera->GetViewRectangle();

		_data->tileMap.DrawBackgroundLayers(_data->tileSet, cameraViewRect);

		auto playerGridLoc = _data->tileMap.WorldToGrid(AllData::PlayerPos.x, AllData::PlayerPos.y);
		auto playerWorldGrid = _data->tileMap.GridToWorld(playerGridLoc.y, playerGridLoc.x);

		Graphics::Get()->DrawTile(_data->tileSet, 960, playerWorldGrid, 100);
		AllData::PlayerSprite.DrawSprite(AllData::PlayerPos, AllData::PlayerLayer);

		_data->tileMap.DrawForegroundLayers(_data->tileSet, cameraViewRect);
	}
}