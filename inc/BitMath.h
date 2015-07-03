#ifndef __RUIN2D_BITMATH_H_
#define __RUIN2D_BITMATH_H_

#include <stdint.h>

namespace Ruin2D
{
	namespace Math
	{
		/* Returns the next highest power of 2 relative to the given 32 bit integer. */
		uint32_t NextHighestPower2(uint32_t v);

		/* Returns the Log base 2 of a 32 bit integer. */
		uint32_t Log2(uint32_t v);
	}
}

#endif