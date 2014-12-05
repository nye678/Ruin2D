#include "ScopeStack.h"
#include <cstring>
#include <new>

using namespace Ruin2D;

ScopeStack::ScopeStack(LinearAllocator& allocator)
	: _allocator(allocator), _rewindPoint(nullptr), _headerChain(nullptr)
{
	_rewindPoint = _allocator.Alloc(Alignment);
	strcpy_s(static_cast<char*>(_rewindPoint), Alignment, "--Scope Stack--");
}

ScopeStack::~ScopeStack()
{
	for (auto itor = _headerChain; itor != nullptr; itor = itor->chain)
	{
		itor->destroyObject(ObjectPointerFromHeader(itor));
	}

	_allocator.Rewind(_rewindPoint);
}

void* ScopeStack::Alloc(size_t size)
{
	return _allocator.Alloc(size);
}

ScopeStack::ObjectHeader* ScopeStack::AllocWithHeader(size_t size)
{
	return AllocWithHeader(size, 1);
}

ScopeStack::ObjectHeader* ScopeStack::AllocWithHeader(size_t size, size_t count)
{
	void* headerPtr = _allocator.Alloc(sizeof(ObjectHeader));
	void* objectPtr = _allocator.Alloc(size * count);

	auto header = new (headerPtr)ObjectHeader;
	header->count = count;
	header->size = size;

	return header;
}

void* ScopeStack::ObjectPointerFromHeader(ObjectHeader* header)
{
	uintptr_t ptr = reinterpret_cast<uintptr_t>(header) + sizeof(ObjectHeader);
	return AlignPointerNext(ptr, Alignment);
}

ScopeStack::ObjectHeader* ScopeStack::HeaderFromObjectPointer(void* pointer)
{
	uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer) - sizeof(ObjectHeader);
	return static_cast<ObjectHeader*>(AlignPointerPrev(ptr, Alignment).ptr);
}