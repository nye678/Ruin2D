#include "Sprite.h"

using namespace Ruin2D;

Sprite::Sprite()
	: _currentFrame(0), _direction(0), _time(0.0), _fps(1.0/8.0)
{}

Sprite Sprite::Load(const std::string &filepath, int frameWidth, int frameHeight, int rows, int cols)
{
	Sprite sprite;
	sprite._tileSet = TileSet::Load(filepath, frameWidth, frameHeight, rows, cols);

	return sprite;
}

void Sprite::StepFrame(double deltaTime)
{
	_time += deltaTime;
	if (_time >= _fps)
	{
		_currentFrame++;
		if (_currentFrame >= _tileSet.Columns())
		{
			_currentFrame = 0;
		}

		_time = 0.0;
	}
}

void Sprite::SetDirection(int dir)
{
	_direction = dir;
}

void Sprite::DrawSprite(Graphics* graphics, const glm::vec2 &position, short layer)
{
	auto spriteDrawPos = position;
	spriteDrawPos.y -= _tileSet.TileHeight();
	spriteDrawPos.x -= _tileSet.TileWidth() / 2.0f;
	
	graphics->DrawTile(
		_tileSet,
		_currentFrame +_tileSet.Columns() * _direction,
		spriteDrawPos, layer);
}