#include "EntityData.h"

using namespace glm;
using namespace Ruin2D;

EntityData::EntityData(int maxEntities)
	: _position(nullptr), _scale(nullptr), _orientation(nullptr), _maxEntities(maxEntities)
{
	_position = new vec2[maxEntities];
	_scale = new vec2[maxEntities];
	_orientation = new double[maxEntities];
}

EntityData::EntityData(const EntityData &&other)
{
	_maxEntities = other._maxEntities;
	_position = other._position;
	_scale = other._scale;
	_orientation = other._orientation;
}

EntityData::~EntityData()
{
	if (_orientation != nullptr)
	{
		delete[] _orientation;
		_orientation = nullptr;
	}

	if (_scale != nullptr)
	{
		delete[] _scale;
		_scale = nullptr;
	}

	if (_position != nullptr)
	{
		delete[] _position;
		_position = nullptr;
	}
}
