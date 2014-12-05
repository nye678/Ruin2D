#include "VirtualMemory.h"

#include <Windows.h>

using namespace Ruin2D;

VirtualMemory::VirtualMemory(size_t pageSize)
	: _baseAddress(nullptr), _nextPage(nullptr), _pages(0), _maxPages(0), _pageSize(pageSize)
{}

void VirtualMemory::Reserve(size_t size)
{
	if (_baseAddress == nullptr)
	{
		void* base = VirtualAlloc(nullptr, size, MEM_RESERVE, PAGE_NOACCESS);

		_baseAddress = static_cast<char*>(base);
		_nextPage = _baseAddress;

		_pages = 0;
		_maxPages = size / _pageSize;
	}
}

void VirtualMemory::Release()
{
	if (_baseAddress != nullptr)
	{
		VirtualFree(_baseAddress, 0, MEM_RELEASE);
		_baseAddress = nullptr;
		_nextPage = nullptr;
		_pages = 0;
		_maxPages = 0;
	}
}

void VirtualMemory::Commit(size_t size)
{
	
}

void VirtualMemory::Decommit(size_t size)
{

}