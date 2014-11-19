#ifndef __RUIN2D_LOCALMAPDATA_H_
#define __RUIN2D_LOCALMAPDATA_H_

#include <unordered_map>

#include "EntityData.h"
#include "TileMap.h"
#include "Sprite.h"

namespace Ruin2D
{
	struct LocalMapData
	{
		TileMap tileMap;
		TileSet tileSet;
		//Trigger Regions
		//Boundry Regions
	};
}

#endif