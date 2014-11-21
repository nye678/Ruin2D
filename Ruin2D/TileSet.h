#ifndef __RUIN2D_TILESET_H_
#define __RUIN2D_TILESET_H_

#include <cmath>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <rapidjson\document.h>
#include "Texture.h"
#include "Utility.h"

namespace Ruin2D
{
	/* TileSet
	   Image tileset class for retrieving individual tile uv information. UVs are
	   composed in a 3x3 vector which is used as an input to the shader. */
	class TileSet
	{
	private:
		int _tileWidth;
		int _tileHeight;
		int _rows;
		int _columns;

		std::string _name;
		Texture _texture;

	public:
		static TileSet Parse(const std::string &filepath, const rapidjson::Document &doc, int setIndex);
		
		static TileSet Load(const std::string &filepath, int tileWidth, int tileHeight, int rows, int columns);

		GLuint Handle() const;

		GLint Unit() const;

		int TileWidth() const;

		int TileHeight() const;

		int Rows() const;

		int Columns() const;

		glm::mat3 GetTileUVMatrix(int tileIndex) const;

		TileSet();
	};
}

#endif