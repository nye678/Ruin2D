#ifndef __RUIN2D_SPRITE_H_
#define __RUIN2D_SPRITE_H_

#include "TileSet.h"
#include "Graphics.h"
#include "TextureManager.h"

namespace Ruin2D
{
	class Sprite
	{
	private:
		int _currentFrame;
		int _direction;
		double _time;
		double _fps;

		TileSet _tileSet;

	public:
		static Sprite Load(const std::string &filepath, int frameWidth, int frameHeight, int rows, int cols);

		void StepFrame(double deltaTime);

		void SetDirection(int dir);

		void DrawSprite(const glm::vec2 &position);

		Sprite();
	};
}

#endif