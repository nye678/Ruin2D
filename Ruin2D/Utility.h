#ifndef __RUIN2D_UTILITY_H_
#define __RUIN2D_UTILITY_H_

#include <cstdio>
#include <string>
#include <sys\stat.h>

namespace Ruin2D
{
	/* Load Text File
	   Loads the contents of a text file into a char buffer. If the is an error
	   reading the file a zero is returned and the buffer is invalid. */
	size_t LoadTextFile(const char* filepath, char* &buffer);
}

#endif