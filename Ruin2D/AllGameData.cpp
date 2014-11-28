#include "AllGameData.h"

using namespace Ruin2D;
using namespace Ruin2DGame;

LocalMapData*	AllData::TestMap = nullptr;
Sprite			AllData::PlayerSprite;
glm::vec2		AllData::PlayerPos;
short			AllData::PlayerLayer;
bool			AllData::PlayerOnStairs;

void AllData::LoadAllData()
{
	// Load maps.
	TestMap = LocalMapData::LoadMapData("D:\\Projects\\Ruin2D\\Data\\Maps\\testmap.json");

	// Player stuff.
	PlayerSprite = Sprite::Load("D:\\Projects\\Ruin2D\\Data\\Textures\\rpg_sprite_walk.png", 24, 32, 8, 4);
	//PlayerSprite = Sprite::Load("D:\\Projects\\Ruin2D\\Data\\Textures\\debugsprite.png", 24, 32, 8, 4);
	PlayerPos = glm::vec2(20.0, 20.0);
	PlayerLayer = 2;
	PlayerOnStairs = false;
}