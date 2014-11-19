#include "TileSet.h"

using namespace std;
//using namespace glm;
using namespace Ruin2D;

TileSet::TileSet()
	: _tileWidth(0), _tileHeight(0), _rows(0), _columns(0)
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

	string dir = GetDirectoryFromFilepath(filepath);
	string textureFilepath = CombinePath(dir, tileSetDoc["image"].GetString());

	tileSet._texture = Texture::Load(textureFilepath);

	return tileSet;
}