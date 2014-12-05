#ifndef __RUIN2D_POINTERUTILS_H_
#define __RUIN2D_POINTERUTILS_H_

#include <cstdint>

namespace Ruin2D
{
	/* Omni Pointer union type */
	/* Designed to do everything normal pointers do. Except for a reduction
	   in silly type casting just to do minor pointer arithmetic. */
	union OmniPointer
	{
		void* ptr;
		char* charPtr;
		uintptr_t intPtr;

		inline operator bool()
		{
			return ptr != nullptr;
		}

		inline operator void*()
		{
			return ptr;
		}

		inline operator char*()
		{
			return charPtr;
		}

		inline operator uintptr_t()
		{
			return intPtr;
		}

		OmniPointer() : ptr(nullptr) {}
		OmniPointer(void* ptr) : ptr(ptr) {}
		OmniPointer(char* ptr) : charPtr(ptr) {}
		OmniPointer(uintptr_t intPtr) : intPtr(intPtr) {}
		OmniPointer(std::nullptr_t np) : ptr(np) {}
	};

	inline OmniPointer operator+ (OmniPointer lhs, size_t offset)
	{
		return lhs.intPtr + offset;
	}

	inline OmniPointer operator- (OmniPointer lhs, size_t offset)
	{
		return lhs.intPtr - offset;
	}

	inline OmniPointer operator+ (OmniPointer lhs, int offset)
	{
		return lhs.intPtr + offset;
	}

	inline OmniPointer operator- (OmniPointer lhs, int offset)
	{
		return lhs.intPtr - offset;
	}

	inline bool operator> (OmniPointer lhs, OmniPointer rhs)
	{
		return lhs.intPtr > rhs.intPtr;
	}

	inline bool operator>= (OmniPointer lhs, OmniPointer rhs)
	{
		return lhs.intPtr >= rhs.intPtr;
	}

	inline bool operator< (OmniPointer lhs, OmniPointer rhs)
	{
		return lhs.intPtr < rhs.intPtr;
	}

	inline bool operator<= (OmniPointer lhs, OmniPointer rhs)
	{
		return lhs.intPtr <= rhs.intPtr;
	}

	inline OmniPointer operator& (OmniPointer ptr, uintptr_t mask)
	{
		return ptr.intPtr & mask;
	}

	inline OmniPointer AlignPointerNext(OmniPointer ptr, size_t align)
	{
		uintptr_t mask = ~(uintptr_t)(align - 1);
		OmniPointer alignedPtr = (ptr + align - 1) & mask;

		return alignedPtr;
	}

	inline OmniPointer AlignPointerPrev(OmniPointer ptr, size_t align)
	{
		uintptr_t mask = ~(uintptr_t)(align - 1);
		OmniPointer alignedPtr = (ptr) & mask;

		return alignedPtr;
	}
}

#endif