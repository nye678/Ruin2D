#ifndef __RUIN2D_ASSERT_H_
#define __RUIN2D_ASSERT_H_

#include <Windows.h>

#ifdef _DEBUG
#define Assert(condition, message) \
{ \
	if (!(condition)) \
	{ \
		char msgBuffer[1024];\
		sprintf_s(msgBuffer, 1024, "An assertion has failed at %s:%d\n\n%s", __FILE__, __LINE__, message);\
		int dialogResult = MessageBox(nullptr, msgBuffer, "Assertion!", MB_ABORTRETRYIGNORE | MB_ICONERROR);\
		\
		switch (dialogResult)\
		{\
		case IDABORT:\
			exit(1);\
			break;\
		case IDRETRY:\
			__debugbreak();\
			break;\
		case IDIGNORE:\
		\
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