#ifndef __RUIN2D_TILEMAP_H_
#define __RUIN2D_TILEMAP_H_

#include <string>
#include <vector>
#include <glm\glm.hpp>
#include <cmath>

#include <rapidjson\document.h>
#include "TileSet.h"
#include "Utility.h"
#include "Graphics.h"

namespace Ruin2D
{
	class TileMap
	{
		struct MapLayer
		{
			short* tiles;
			char* tileType;
			int width;
			int height;
			int x;
			int y;

			bool visible;
			std::string name;
		};

	private:
		static const int NullTile = -1;

		int _width;
		int _height;
		int _tilewidth;
		int _tileheight;

		int _numlayers;
		MapLayer* _layers;

		std::string _name;

		int GetIndex(int row, int col);

		int GetRow(int index);

		int GetColumn(int index);

		glm::ivec2 PointToGridCoords(int x, int y);

		glm::vec2 GridToWorld(int row, int col);

		glm::ivec2 WorldToGrid(double x, double y);
	public:
		static TileMap Parse(const rapidjson::Document &doc);

		std::string Name() const;

		void DrawBackgroundLayers(const TileSet &tileSet, const glm::ivec4 &rect);

		void DrawForegroundLayers(const TileSet &tileSet, const glm::ivec4 &rect);

		void DrawMapSection(const TileSet &tileSet, const glm::ivec4 &rect, int layer);

		TileMap();
	};
}

#endif