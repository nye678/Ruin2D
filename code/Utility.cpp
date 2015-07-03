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
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		rewind(file);

		buffer = new char[size + 1];
		memset(buffer, 0x00, size + 1);
		read = fread_s(buffer, size + 1, 1, size, file);
		buffer[read] = 0x00;

		if (read == 0)
		{
			delete[] buffer;
		}

		fclose(file);
	}

	return read;
}
