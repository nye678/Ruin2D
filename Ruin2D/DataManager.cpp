#include "DataManager.h"

using namespace std;
using namespace Ruin2D;

DataManager::DataManager()
{}

DataManager::~DataManager()
{
	LocalMapData* localMap = nullptr;
	for (auto localMapPair : _localMaps)
	{
		localMap = localMapPair.second;
		localMapPair.second = nullptr;

		if (localMap != nullptr)
		{
			delete localMap;
			localMap = nullptr;
		}
	}

	_localMaps.clear();
}

shared_ptr<DataManager> DataManager::Create()
{
	return Singleton.Create();
}

void DataManager::LoadLocalMap(const std::string &filepath)
{
	char* buffer;
	size_t read = LoadTextFile(filepath.c_str(), buffer);

	Assert_True(read > 0, "Failed to read any data from the provided file.");

	rapidjson::Document doc;
	doc.Parse<0>(buffer);
	delete buffer;

	LocalMapData* localmap = new LocalMapData();
	localmap->tileMap = TileMap::Parse(doc);
	localmap->tileSet = TileSet::Parse(filepath, doc, 0);

	_localMaps.insert(make_pair(localmap->tileMap.Name(), localmap));
}

LocalMapData* DataManager::GetLocalMap(const std::string &name)
{
	return _localMaps[name];
}