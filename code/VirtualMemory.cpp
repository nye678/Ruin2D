#include "VirtualMemory.h"

#include <Windows.h>

using namespace Ruin2D::VirtualMemory;

void* Ruin2D::VirtualMemory::Reserve(size_t size)
{
	return VirtualAlloc(nullptr, size, MEM_RESERVE, PAGE_NOACCESS);
}

void Ruin2D::VirtualMemory::Release(void* pointer)
{
	VirtualFree(pointer, 0, MEM_RELEASE);
}

void* Ruin2D::VirtualMemory::Commit(void* pointer, size_t size)
{
	return VirtualAlloc(pointer, size, MEM_COMMIT, PAGE_READWRITE);
}

void Ruin2D::VirtualMemory::Decommit(void* pointer, size_t size)
{
	VirtualFree(pointer, size, MEM_DECOMMIT);
}