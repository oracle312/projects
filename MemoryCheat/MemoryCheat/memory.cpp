#include "memory.h"

void memory::HackPatch(BYTE* addr, BYTE* buf, unsigned int size, HANDLE hProc)
{
	DWORD oldProtect;
	VirtualProtectEx(hProc, addr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProc, addr, buf, size, NULL);
	VirtualProtectEx(hProc, addr, size, oldProtect, &oldProtect);
}