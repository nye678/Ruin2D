#include "TileMap.h"
#include "Utility.h"

using namespace std;
using namespace rapidjson;
using namespace Ruin2D;

TileMap::TileMap()
	: _width(0), _height(0), _tilewidth(0), _tileheight(0), _numlayers(0), _layers(nullptr)
{}

string TileMap::Name() const
{
	return _name;
}

int TileMap::GetIndex(int row, int col)
{
	return col + (row * _width);
}

int TileMap::GetRow(int index)
{
	return (int)floor((double)index / (double)_width);
}

int TileMap::GetColumn(int index)
{
	return index % _width;
}

void TileMap::DrawBackgroundLayers(Graphics* graphics, const TileSet &tileSet, const glm::ivec4 &rect)
{
	for (int i = 0; i < _numlayers; ++i)
	{
		DrawMapSection(graphics, tileSet, rect, i);
	}
}

glm::ivec2 TileMap::PointToGridCoords(int x, int y)
{
	glm::ivec2 gridCoords;
	gridCoords.x = x * _tilewidth;
	gridCoords.y = y * _tileheight;

	return gridCoords;
}

glm::vec2 TileMap::GridToWorld(int row, int col)
{
	return glm::vec2((float)col * _tilewidth, (float)row * _tileheight);
}

glm::ivec2 TileMap::WorldToGrid(double x, double y)
{
	return glm::ivec2((float)x / _tilewidth, (float)y / _tileheight);
}

short TileMap::GetTile(int row, int col, int layer)
{
	return _layers[layer].tiles[GetIndex(row, col)];
}

void TileMap::DrawForegroundLayers(Graphics* graphics, const TileSet &tileSet, const glm::ivec4 &rect)
{

}

void TileMap::DrawMapSection(Graphics* graphics, const TileSet &tileSet, const glm::ivec4 &rect, int layerIndex)
{
	auto topleft = WorldToGrid(-rect.x, rect.y);
	auto bottomright = WorldToGrid(rect.z, rect.w);

	int firstRow = glm::max(topleft.y , 0);
	int firstCol = glm::max(topleft.x, 0);
	int lastRow = glm::min(bottomright.y + topleft.y + 1, _height);
	int lastCol = glm::min(bottomright.x + topleft.x + 1, _width);

	if (layerIndex < _numlayers)
	{
		MapLayer* layer = &_layers[layerIndex];
		if (layer->visible)
		{
			for (int row = firstRow; row < lastRow; ++row)
			{
				for (int col = firstCol; col < lastCol; ++col)
				{
					int index = GetIndex(row, col);
					if (index >= 0 && index < _width * _height)
					{
						int tileIndex = layer->tiles[index];
						if (tileIndex >= 0)
						{
							auto tileProperties = tileSet.GetTileProperties(tileIndex);
							if (tileProperties.visible)
							{
								auto position = GridToWorld(row, col);
								graphics->DrawTile(tileSet, tileIndex, position, layerIndex);
							}

							/*if (tileProperties.blocking)
							{
								auto position = GridToWorld(row, col);
								graphics->DrawTile(tileSet, 992, position, 100);
							}*/
						}
					}
				}
			}
		}
	}
}

TileMap TileMap::Parse(const Document &doc)
{
	TileMap tileMap;

	tileMap._width = doc["width"].GetInt();
	tileMap._height = doc["height"].GetInt();
	tileMap._tilewidth = doc["tilewidth"].GetInt();
	tileMap._tileheight = doc["tileheight"].GetInt();

	const Value &properties = doc["properties"];
	tileMap._name = properties["name"].GetString();
	
	const Value &layers = doc["layers"];

	tileMap._numlayers = layers.Size();
	tileMap._layers = new MapLayer[tileMap._numlayers];

	for (unsigned int layerIndex = 0; layerIndex < layers.Size(); ++layerIndex)
	{
		MapLayer* layer = &tileMap._layers[layerIndex];
		const Value &layerdoc = layers[layerIndex];

		layer->width = layerdoc["width"].GetInt();
		layer->height = layerdoc["height"].GetInt();
		layer->x = layerdoc["x"].GetInt();
		layer->y = layerdoc["y"].GetInt();
		layer->visible = layerdoc["visible"].GetBool();
		layer->name = layerdoc["name"].GetString();
		
		const Value &data = layerdoc["data"];
		layer->tiles = new short[layer->width * layer->height];

		for (unsigned int dataIndex = 0; dataIndex < data.Size(); ++dataIndex)
		{
			short tile = (short)(data[dataIndex].GetInt() - 1);
			layer->tiles[dataIndex] = (short)(tile);
		}
	}

	return tileMap;
}

