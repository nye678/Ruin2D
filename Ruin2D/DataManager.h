#ifndef __RUIN2D_DATAMANAGER_H_
#define __RUIN2D_DATAMANAGER_H_

#include <string>
#include <unordered_map>
#include <rapidjson\document.h>

#include "LocalMapData.h"
#include "Singleton.h"

namespace Ruin2D
{
	class DataManager
	{
		friend class Singleton<DataManager>;

	private:
		static Singleton<DataManager> Singleton;

		std::unordered_map<std::string, LocalMapData*> _localMaps;

	public:
		static std::shared_ptr<DataManager> Create();

		inline static std::shared_ptr<DataManager> Get()
		{
			return Singleton.Get();
		}

		void LoadLocalMap(const std::string &filepath);

		LocalMapData* GetLocalMap(const std::string &name);

	private:
		DataManager();
		DataManager(const DataManager &) = delete;
		DataManager &operator= (const DataManager &) = delete;
	public:
		~DataManager();
	};
}

#endif