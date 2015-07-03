#ifndef __RUIN2D_TILEMAP_H_
#define __RUIN2D_TILEMAP_H_

#include <cassert>
#include <string>
#include <glm\glm.hpp>
#include <rapidjson\document.h>
#include "TileSet.h"
#include "Graphics.h"

namespace Ruin2D
{
	/* TileMap Class */
	/* A tile map is a regular grid map with 1 or more layers decorated by
	   a tile set. */
	class TileMap
	{
		// A layer in a tile map. 
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

	public:
		// Converts a grid position into world coordinates. Will be the
		// upper left corner of the grid.
		glm::vec2 GridToWorld(int row, int col);

		// Converts world coordinates to grid coordinates.
		glm::ivec2 WorldToGrid(double x, double y);

		// Gets the grid index using the given grid coordinates.
		int GetIndex(int row, int col);

		// Gets the tile index used in the tile map at the given grid coordinates and layer.
		short GetTile(int row, int col, int layer);

		// Parses tile map data from a json document.
		static TileMap Parse(const rapidjson::Document &doc);

		// Returns the name of the tile map.
		std::string Name() const;

		// Draws the background layers of the tile map.
		void DrawBackgroundLayers(Graphics* graphics, const TileSet &tileSet, const glm::ivec4 &rect);

		// Draws the foreground layers of the tile map.
		void DrawForegroundLayers(Graphics* graphics, const TileSet &tileSet, const glm::ivec4 &rect);

		// Draws a section of a tile map layer.
		void DrawMapSection(Graphics* graphics, const TileSet &tileSet, const glm::ivec4 &rect, int layer);

	private:
		// Gets the grid row from a grid index.
		int GetRow(int index);

		// Gets the column from a grid index.
		int GetColumn(int index);

		// Converts a point to grid coordinates.
		glm::ivec2 PointToGridCoords(int x, int y);

	public:
		TileMap();
	};
}

#endif