#ifndef __RUIN2D_SPRITE_H_
#define __RUIN2D_SPRITE_H_

#include "TileSet.h"
#include "Graphics.h"

namespace Ruin2D
{
	/* Sprite Class */
	/* A sprite represented an animated texture. It only holds informat for that
	   purpose and does not care about other functions such as where it positioned
	   in the world and such. Sprites will have a number of animations and animation
	   transitions which can (will be soon) parsed from data files. */
	class Sprite
	{
	private:
		int _currentFrame;
		int _direction;
		double _time;
		double _fps;

		TileSet _tileSet;

	public:
		/* Loads sprite data into memory and returns a newly created sprite.
		   Each sprite is unique but can share texture data with multiple copies. */
		static Sprite Load(const std::string &filepath, int frameWidth, int frameHeight, int rows, int cols);

		/* Advances the sprite's animation by one frame. */
		void StepFrame(double deltaTime);

		/* Sets the facing direction of sprite. */
		void SetDirection(int dir);

		/* Draws the sprite at the given position and layer. */
		void DrawSprite(Graphics* graphics, const glm::vec2 &position, short layer);

		Sprite();

	};
}

#endif