#ifndef __RUIN2D_LOG_H_
#define __RUIN2D_LOG_H_

#include <cstdio>
#include <string>

namespace Ruin2D
{
	/* Simple logging class. */
	class Log
	{
	private:
		static const char* InfoFormat;
		static const char* ErrorFormat;

	public:
		/* Info
		   Logs an info message. */
		static void Info(const std::string &message);

		/* Info
		   Logs an info message. */
		static void Info(const char* message);

		/* Error
		   Logs an error message. */
		static void Error(const std::string &message);

		/* Error
		   Logs an error message. */
		static void Error(const char* message);

	private:
		Log();
		Log(const Log &) = delete;
		Log &operator= (const Log &) = delete;
	};
}

#endif