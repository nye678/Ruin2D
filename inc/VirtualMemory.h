#ifndef __RUIN2D__VIRTUALMEMORY_H_
#define __RUIN2D__VIRTUALMEMORY_H_

namespace Ruin2D
{
	namespace VirtualMemory
	{
		void* Reserve(size_t size);

		void Release(void* pointer);

		void* Commit(void* pointer, size_t size);

		void Decommit(void* pointer, size_t size);
	};
}

#endif