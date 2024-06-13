#include <windows.h>

namespace memory
{
	void HackPatch(BYTE* addr, BYTE* buf, unsigned int size, HANDLE hProc);
}