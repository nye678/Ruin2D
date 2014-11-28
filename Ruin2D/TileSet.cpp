#include "TileSet.h"

using namespace std;
using namespace Ruin2D;

TileSet::TileSet()
	: _tileWidth(0), _tileHeight(0), _rows(0), _columns(0), _properties(nullptr)
{}

GLuint TileSet::Handle() const
{
	return _texture.Handle();
}

GLint TileSet::Unit() const
{
	return _texture.Unit();
}

int TileSet::TileWidth() const
{
	return _tileWidth;
}

int TileSet::TileHeight() const
{
	return _tileHeight;
}

int TileSet::Rows() const
{
	return _rows;
}

int TileSet::Columns() const
{
	return _columns;
}

TileSet::TileProperties TileSet::GetTileProperties(int tileIndex) const
{
	return _properties[tileIndex];
}

glm::mat3 TileSet::GetTileUVMatrix(int tileIndex) const
{
	int x = tileIndex % _columns;
	int y = (int)floor((float)tileIndex / (float)_columns);

	glm::mat3 uvMatrix = glm::mat3(1.0f);
	uvMatrix[2].x = (float)x * (float)_tileWidth / (float)_texture.Width();
	uvMatrix[2].y = (float)-y * (float)_tileHeight / (float)_texture.Height();
	uvMatrix[0].x = (float)_tileWidth / (float)_texture.Width();
	uvMatrix[1].y = (float)_tileHeight / (float)_texture.Height();

	return uvMatrix;
}

TileSet TileSet::Parse(const string& filepath, const rapidjson::Document &doc, int tileSetIndex)
{
	const rapidjson::Value &tileSetDoc = doc["tilesets"][tileSetIndex];

	TileSet tileSet;
	tileSet._tileWidth = tileSetDoc["tilewidth"].GetInt();
	tileSet._tileHeight = tileSetDoc["tileheight"].GetInt();;
	tileSet._rows = tileSetDoc["imagewidth"].GetInt() / tileSet._tileWidth;
	tileSet._columns = tileSetDoc["imageheight"].GetInt() / tileSet._tileHeight;
	tileSet._name = tileSetDoc["name"].GetString();

	tileSet._properties = new TileProperties[tileSet._rows * tileSet._columns];
	if (tileSetDoc.HasMember("tileproperties"))
	{
		const rapidjson::Value &tileProperties = tileSetDoc["tileproperties"];
		for (auto tileItor = tileProperties.MemberBegin(); tileItor != tileProperties.MemberEnd(); ++tileItor)
		{
			int tile = stoi(tileItor->name.GetString());

			TileProperties* properties = &tileSet._properties[tile];
			if (tileItor->value.HasMember("block"))
			{
				properties->blocking = strcmp(tileItor->value["block"].GetString(), "true") == 0;
			}

			if (tileItor->value.HasMember("stair"))
			{
				properties->stair = strcmp(tileItor->value["stair"].GetString(), "true") == 0;
			}

			if (tileItor->value.HasMember("visible"))
			{
				properties->visible = strcmp(tileItor->value["visible"].GetString(), "true") == 0;
			}
		}
	}

	string dir = GetDirectoryFromFilepath(filepath);
	string textureFilepath = CombinePath(dir, tileSetDoc["image"].GetString());

	tileSet._texture = Texture::Load(textureFilepath);

	return tileSet;
}

TileSet TileSet::Load(const string &filepath, int tileWidth, int tileHeight, int rows, int columns)
{
	TileSet tileSet;
	tileSet._tileWidth = tileWidth;
	tileSet._tileHeight = tileHeight;
	tileSet._rows = rows;
	tileSet._columns = columns;
	tileSet._texture = Texture::Load(filepath);

	return tileSet;
}