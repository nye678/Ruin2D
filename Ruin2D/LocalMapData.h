#ifndef __RUIN2DGAME_LOCALMAPDATA_H_
#define __RUIN2DGAME_LOCALMAPDATA_H_

#include <unordered_map>

#include "TileMap.h"
#include "TileSet.h"

namespace Ruin2DGame
{
	struct LocalMapData
	{
		Ruin2D::TileMap tileMap;
		Ruin2D::TileSet tileSet;

		static LocalMapData* LoadMapData(const std::string &filepath);
	};
}

#endif