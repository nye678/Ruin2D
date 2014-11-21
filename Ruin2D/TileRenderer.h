#ifndef __RUIN2D_TILERENDERER_H_
#define __RUIN2D_TILERENDERER_H_

#include "Graphics.h"

namespace Ruin2D
{
	struct TileInfo
	{
		short mapIndex;
		short tileIndex;
	};

	struct TileMapInfo
	{
		short mapWidth;
		short mapHeight;
		short tileWidth;
		short tileHeight;
	};

	class TileRenderer
	{
	private:
		GLuint vertexArray;
		GLuint tileMapBuffer;
		GLuint tileIndexBuffer;

		GLuint tileMaterial;
		GLint cameraLoc;
		

	public:
	};
}

#endif