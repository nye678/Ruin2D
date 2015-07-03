#include "LocalMapData.h"
#include "Utility.h"

using namespace std;
using namespace Ruin2D;
using namespace Ruin2DGame;

LocalMapData* LocalMapData::LoadMapData(const string &filepath)
{
	char* buffer;
	size_t read = LoadTextFile(filepath.c_str(), buffer);

	Assert(read > 0, "Failed to read any data from the provided file.");

	rapidjson::Document doc;
	doc.Parse<0>(buffer);
	delete buffer;

	if (doc.HasParseError())
	{
		Assert_Fail("Failed to parse json document.");
	}

	LocalMapData* localmap = new LocalMapData();
	localmap->tileMap = TileMap::Parse(doc);
	localmap->tileSet = TileSet::Parse(filepath, doc, 0);

	return localmap;
}