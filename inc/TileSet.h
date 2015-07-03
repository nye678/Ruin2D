#ifndef __RUIN2D_TILESET_H_
#define __RUIN2D_TILESET_H_

#include <cassert>
#include <string>
#include <glm\glm.hpp>
#include <rapidjson\document.h>
#include "Texture.h"

namespace Ruin2D
{
	/* TileSet */
	/* Image tileset class for retrieving individual tile uv information. UVs are
	   composed in a 3x3 vector which is used as an input to the shader. */
	class TileSet
	{
		// Individual properties for a tile. Each tile can have different properties.
		struct TileProperties
		{
			bool blocking;
			bool stair;
			bool visible;

			TileProperties() : blocking(false), stair(false), visible(true) {}
		};

	private:
		int _tileWidth;
		int _tileHeight;
		int _rows;
		int _columns;

		std::string _name;

		Texture _texture;

		TileProperties* _properties;

	public:
		// Parses tile set data from json.
		static TileSet Parse(const std::string &filepath, const rapidjson::Document &doc, int setIndex);
		
		// Manually creates a tile set.
		static TileSet Load(const std::string &filepath, int tileWidth, int tileHeight, int rows, int columns);

		// Gets the texture handle of the tile set.
		GLuint Handle() const;

		// Gets the unit the texture is bound to.
		GLint Unit() const;

		// Gets the width of the tiles in the tile set.
		int TileWidth() const;

		// Gets the height of the tiles in the tile set.
		int TileHeight() const;

		// Gets the number of rows in the tile set.
		int Rows() const;

		// Gets the number of columns in the tile set.
		int Columns() const;

		// Gets the tile properties for the tile at the given index.
		TileProperties GetTileProperties(int tileIndex) const;

		// Get a matrix which is used to transform uv coordinates for a given tile index.
		glm::mat3 GetTileUVMatrix(int tileIndex) const;

		TileSet();
	};
}

#endif