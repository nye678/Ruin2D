#include "SystemInfo.h"

#include <Windows.h>

using namespace Ruin2D;

SystemInfo::SystemInfo()
	: _pageSize(0)
{}

SystemInfo SystemInfo::GetInfo()
{
	SYSTEM_INFO winSysInfo;
	GetSystemInfo(&winSysInfo);

	SystemInfo info;
	info._pageSize = winSysInfo.dwPageSize;

	// Can add more stuff later when it is needed.
	return info;
}