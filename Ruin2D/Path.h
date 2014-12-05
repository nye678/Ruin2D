#ifndef __RUIN2D_PATH_H_
#define __RUIN2D_PATH_H_

#include <string>

namespace Ruin2D
{
	namespace Path
	{
		/* Returns directory of a filepath. */
		std::string GetDirectoryFromFilepath(const std::string &filepath)
		{
			return filepath.substr(0, filepath.find_last_of('\\'));
		}

		std::string CombinePath(const std::string &path1, const std::string &path2)
		{
			return path1 + "\\" + path2;
		}
	}
}

#endif