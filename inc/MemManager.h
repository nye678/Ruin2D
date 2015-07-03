#ifndef __RUIN2D_MEMMANAGER_H_
#define __RUIN2D_MEMMANAGER_H_

#include <stdint.h>
#include "PointerUtils.h"

namespace Ruin2D
{
	class MemManager
	{
		struct FreeList
		{
			FreeList* next;
		};

		typedef uint32_t BoundaryTag;

		static const size_t NumFreeLists = 9;

	private:
		size_t _reserved;
		size_t _commited;

		OmniPointer _head;
		OmniPointer _tail;

		FreeList* _freeList;

	public:
		void* Alloc(size_t size);
		void Free(void* ptr);

	private:
		OmniPointer FindNextFree(size_t size);
		void SplitBlock(OmniPointer block, size_t size);

		BoundaryTag* GetBlockTag(OmniPointer ptr);
		BoundaryTag* GetBlockEndTag(OmniPointer ptr);
		BoundaryTag* GetBlockEndTag(OmniPointer ptr, size_t size);
		BoundaryTag* GetNextBlockTag(OmniPointer ptr);
		BoundaryTag* GetPrevBlockTag(OmniPointer ptr);

	public:
		MemManager(size_t reserve);
		~MemManager();
	};
}

#endif