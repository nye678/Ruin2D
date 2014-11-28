#ifndef __RUIN2DGAME_ALLGAMEDATA_H_
#define __RUIN2DGAME_ALLGAMEDATA_H_

#include <glm\glm.hpp>
#include "LocalMapData.h"
#include "Sprite.h"

namespace Ruin2DGame
{
	struct AllData
	{
		static LocalMapData* TestMap;

		static Ruin2D::Sprite PlayerSprite;
		static glm::vec2 PlayerPos;
		static short PlayerLayer;
		static bool PlayerOnStairs;

		static void LoadAllData();
	};
}

#endif