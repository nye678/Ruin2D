#ifndef __RUIN2D_ASSERT_H_
#define __RUIN2D_ASSERT_H_

#ifdef _DEBUG
#include <cassert>
#include <cstdio>
#include <functional>

#define Assert_Equal(actual, expected, message)\
{\
	if ((actual) != (expected))\
	{\
		fprintf(stderr, "Assertion has failed at %s:%s in function %s\n", __FILE__, __LINE__, __FUNCTION__);\
		fprintf(stderr, "Expected %s, but was %s.\n", #expected, #actual);\
		fprintf(stderr, "%s\n", (message));\
		abort();\
	}\
}

#define Assert_NotEqual(actual, expected, message)\
{\
	if ((actual) == (expected))\
	{\
		fprintf(stderr, "Assertion has failed at %s:%s in function %s\n", __FILE__, __LINE__, __FUNCTION__);\
		fprintf(stderr, "Expected %s, but was %s.\n", #expected, #actual);\
		fprintf(stderr, "%s\n", (message));\
		abort();\
	}\
}

#define Assert_True(condition, message) Assert_Equal((condition), true, message)
#define Assert_False(condition, message) Assert_Equal((condition), false, message)
#define Assert_Null(pointer, message) Assert_Equal(pointer, nullptr, message)
#define Assert_NotNull(pointer, message) Assert_NotEqual(pointer, nullptr, message)

#define Assert_Fail(message)\
{\
	fprintf(stderr, "%s\n", (message));\
	abort();\
}

#else
#define Assert_Equal(actual, expected, message)
#define Assert_NotEqual(actual, expected, message)
#define Assert_True(condition, message)
#define Assert_False(condtion, message)
#define Assert_Null(pointer, message)
#define Assert_NotNull(pointer, message)
#endif

#endif