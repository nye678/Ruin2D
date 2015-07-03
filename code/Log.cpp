#include "Log.h"

using namespace std;
using namespace Ruin2D;

const char* Log::InfoFormat = "Info: %s\n";
const char* Log::ErrorFormat = "Error: %s\n";

Log::Log()
{}

void Log::Info(const std::string &message)
{
	printf(InfoFormat, message);
}

void Log::Info(const char* message)
{
	printf(InfoFormat, message);
}

void Log::Error(const std::string &message)
{
	printf(ErrorFormat, message);
}

void Log::Error(const char* message)
{
	printf(ErrorFormat, message);
}