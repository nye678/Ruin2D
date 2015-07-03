#include "MemManager.h"
#include "VirtualMemory.h"
#include "RuinAssert.h"
#include "BitMath.h"
#include <string.h>

using namespace Ruin2D;

#define BlockTag(ptr) (static_cast<BoundaryTag*>(OmniPointer(ptr) - sizeof(BoundaryTag)))
#define PrevBlockTag(ptr) (static_cast<BoundaryTag*>(OmniPointer(ptr) - (2 * sizeof(BoundaryTag))))
#define BlockLength(tagPtr) (*tagPtr & ~0x01)
#define BlockFree(tagPtr) (*tagPtr & 0x01)
#define SetBlockFree(tagPtr) (*tagPtr |= 0x01)
#define SetBlockAllocated(tagPtr) (*tagPtr &= ~0x01)

#define BlockOverheadSize 2 * sizeof(BoundaryTag) + sizeof(FreeList)

MemManager::MemManager(size_t reserve)
	: _reserved(0), _commited(0), _head(nullptr), _tail(nullptr), _freeList(nullptr)
{
	_head = VirtualMemory::Reserve(reserve);
	Assert_NotNull(_head.ptr, "Failed to reserve memory.");
	_tail = _head;
	_reserved = reserve;
}

MemManager::~MemManager()
{
	if (_head)
	{
		VirtualMemory::Release(_head);
	}
}

void* MemManager::Alloc(size_t size)
{
	return nullptr;
}

OmniPointer MemManager::FindNextFree(size_t size)
{
	// Size required to be a multiple of 2. This is so the 1 bit 
	// can be used as a flag.
	size_t adjustedSize = (size & 0x01) ? size + 1 : size;

	if (!_freeList)
	{
		
	}

	FreeList* previous = nullptr;
	for (auto freeBlock = _freeList; freeBlock; freeBlock = freeBlock->next)
	{
		BoundaryTag* tag = GetBlockTag(freeBlock);
		size_t blockLength = BlockLength(tag);
		if (blockLength >= size)
		{
			if (previous)
			{
				previous->next = freeBlock->next;
			}

			if (blockLength > size + BlockOverheadSize)
			{
				SplitBlock(freeBlock, adjustedSize);
			}

			return freeBlock;
		}
		
		previous = freeBlock;
	}

	return nullptr;
}

void MemManager::SplitBlock(OmniPointer block, size_t size)
{
	BoundaryTag* tag = GetBlockTag(block);
	size_t blockLength = BlockLength(tag);

	BoundaryTag* endTag = GetBlockEndTag(block, blockLength);
	
	OmniPointer newBlock = block + size + (2 * sizeof(BoundaryTag));
	BoundaryTag* newBlockTag = GetBlockTag(newBlock);
	(*newBlockTag) = blockLength - size - (2 * sizeof(BoundaryTag));

}

void MemManager::Free(void* ptr)
{

}

MemManager::BoundaryTag* MemManager::GetBlockTag(OmniPointer ptr)
{
	return static_cast<BoundaryTag*>((ptr - sizeof(BoundaryTag)).ptr);
}

MemManager::BoundaryTag* MemManager::GetBlockEndTag(OmniPointer ptr)
{
	BoundaryTag* tag = GetBlockTag(ptr);
	return static_cast<BoundaryTag*>((ptr + (size_t)BlockLength(tag) + sizeof(BoundaryTag)).ptr);
}

MemManager::BoundaryTag* MemManager::GetBlockEndTag(OmniPointer ptr, size_t size)
{
	return static_cast<BoundaryTag*>((ptr + size + sizeof(BoundaryTag)).ptr);
}

MemManager::BoundaryTag* MemManager::GetNextBlockTag(OmniPointer ptr)
{
	BoundaryTag* tag = GetBlockTag(ptr);
	return static_cast<BoundaryTag*>((ptr + (size_t)BlockLength(tag) + (2 * sizeof(BoundaryTag))).ptr);
}

MemManager::BoundaryTag* MemManager::GetPrevBlockTag(OmniPointer ptr)
{
	return static_cast<BoundaryTag*>((ptr - (2 * sizeof(BoundaryTag))).ptr);
}