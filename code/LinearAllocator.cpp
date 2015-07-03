#include "LinearAllocator.h"
#include <cstring>

using namespace Ruin2D;

LinearAllocator::LinearAllocator(size_t size)
{
	_start = new char[size];
	_end = _start + size;
	_current = _start;

	memset(_start, 0xFE, size);
}

LinearAllocator::~LinearAllocator()
{
	Delete();
}

void* LinearAllocator::Alloc(size_t size)
{
	OmniPointer alignedPtr = AlignPointerNext(_current, DefaultAlign);

	_current = alignedPtr + size;
	if (_current >= _end)
	{
		return nullptr;
	}

	return alignedPtr;
}

void* LinearAllocator::Alloc(size_t size, size_t align, size_t offset)
{
	OmniPointer alignedPtr = AlignPointerNext(_current + offset, align) - offset;
	
	_current = alignedPtr + size;
	if (_current >= _end)
	{
		return nullptr;
	}

	return alignedPtr;
}

void LinearAllocator::Delete()
{
	if (_start)
	{
		delete[] _start.ptr;
	}

	_start = nullptr;
	_end = nullptr;
	_current = nullptr;
}