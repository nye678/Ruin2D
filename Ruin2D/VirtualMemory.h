#ifndef __RUIN2D__VIRTUALMEMORY_H_
#define __RUIN2D__VIRTUALMEMORY_H_

namespace Ruin2D
{
	class VirtualMemory
	{
	private:
		char* _baseAddress;
		char* _nextPage;

		int _pages;
		int _maxPages;
		
		size_t _pageSize;

	public:
		void Reserve(size_t size);

		void Release();

		void Commit(size_t size);

		void Decommit(size_t size);

		VirtualMemory(size_t pageSize);
	};
}

#endif