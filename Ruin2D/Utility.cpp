#include "Utility.h"

using namespace std;
using namespace Ruin2D;

size_t Ruin2D::LoadTextFile(const char* fileName, char* &buffer)
{
	size_t read = 0;
	FILE* file = nullptr;
	errno_t error = fopen_s(&file, fileName, "r");

	if (error == 0)
	{
		int fd = _fileno(file);
		if (fd > -1)
		{
			struct _stat stats;
			if (_fstat(fd, &stats) != -1 && stats.st_size > 0)
			{
				buffer = new char[stats.st_size + 1];
				memset(buffer, '\0', stats.st_size + 1);

				read = fread(buffer, sizeof(char), stats.st_size, file);
				if (read == 0)
				{
					delete[] buffer;
				}
			}
		}

		fclose(file);
	}

	return read;
}

string Ruin2D::GetDirectoryFromFilepath(const string &filepath)
{
	return filepath.substr(0, filepath.find_last_of('\\'));
}

string Ruin2D::CombinePath(const string &path1, const string &path2)
{
	return path1 + "\\" + path2;
}