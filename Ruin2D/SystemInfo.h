#ifndef __RUIN2D_SYSTEMINFO_H_
#define __RUIN2D_SYSTEMINFO_H_

namespace Ruin2D
{
	/* System Info Class */
	/* Holds information about the current system and allows for that information
	   to be queried. */
	class SystemInfo
	{
		// Virtual Memory
		int _pageSize;

	public:
		// Gets the page size for virtual memory allocations.
		inline int PageSize()
		{
			return _pageSize;
		}

		// Gathers system information and returns a new SystemInfo instance.
		static SystemInfo GetInfo();

	private:
		// Use GetSystemInfo.
		SystemInfo();
	};
}

#endif