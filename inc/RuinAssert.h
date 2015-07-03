#ifndef __RUIN2D_ASSERT_H_
#define __RUIN2D_ASSERT_H_

#include <cstdlib>

namespace Ruin2D
{
	namespace Assertion
	{
		enum AssertDialogResult
		{ 
			None,
			Abort, 
			Debug,
			Ignore 
		};

		AssertDialogResult ShowAssertionDialog(const char* message, const char* file, int line);

		size_t FormatAssertMessage(const char* message, const char* file, int line, char* buffer);
	}
}

#ifdef _DEBUG
#define Assert(condition, message) \
{ \
	namespace R2DA = Ruin2D::Assertion; \
	if (!(condition)) \
	{ \
		R2DA::AssertDialogResult dialogResult = R2DA::ShowAssertionDialog(message, __FILE__, __LINE__); \
		\
		switch (dialogResult)\
		{\
		case R2DA::AssertDialogResult::Abort:\
			exit(1);\
			break;\
		case R2DA::AssertDialogResult::Debug:\
			__debugbreak();\
			break;\
		case R2DA::AssertDialogResult::Ignore:\
			break;\
		}\
	} \
}

#define Assert_NotNull(pointer, message) \
{\
	Assert((pointer != nullptr), message); \
}

#define Assert_Fail(message) Assert(false, message)

#else
#define Assert(condition, message) (condition)

#define Assert_NotNull(pointer, message) (pointer)

#define Assert_Fail(message) 
#endif

#endif