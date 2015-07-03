#ifndef __RUIN2D_FILE_H_
#define __RUIN2D_FILE_H_

#include <string>

namespace Ruin2D
{
	class File
	{
	public:
		static std::string ReadAllText(const std::string &filepath);
	};
}

#endif