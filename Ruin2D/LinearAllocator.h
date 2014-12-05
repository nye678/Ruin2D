#ifndef __RUIN2D_LINEARALLOCATOR_H_
#define __RUIN2D_LINEARALLOCATOR_H_

#include "PointerUtils.h"

namespace Ruin2D
{
	/* Linear Allocator Class */
	/* An allocator which holds a large chunk of memory and allocates
	   chunks linearly. The allocator can be rewound to clear up memory.
	   Care will need to be take so that memory is not prematurely freed.*/
	class LinearAllocator
	{
	private:
		const size_t DefaultAlign = 16;

		OmniPointer _start;
		OmniPointer _end;
		OmniPointer _current;

	public:
		/* Allocates a raw chunk of memory. */
		void* Alloc(size_t size);

		void* Alloc(size_t size, size_t align, size_t offset);

		/* Rewinds the allocator freeing all memory below the given pointer.
		   Anything allocated after this pointer will be considered free. */
		inline void Rewind(void* pointer)
		{
			_current = pointer;
		}

		/* Resets the allocator freeing all memory. */
		inline void Reset()
		{
			_current = _start;
		}

		/* Deletes the memory associated with the allocator. Do not attempt
		   to use the allocator after delete is called. */
		void Delete();

	public:
		/* Constructs a new allocator with backing memory of the given size. */
		LinearAllocator(size_t size);

		~LinearAllocator();
	};
}

#endif