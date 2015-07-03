#include "BitMath.h"

using namespace Ruin2D::Math;

/* See http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2 for more details. */
uint32_t Ruin2D::Math::NextHighestPower2(uint32_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

static const char LogTable256[256] =
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
	- 1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
	LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
	LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

/* See http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogLookup */
uint32_t Ruin2D::Math::Log2(uint32_t v)
{
	uint32_t t, tt;
	if (tt = v >> 16)
	{
		return (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
	}
	else
	{
		return (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
	}
}