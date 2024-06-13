#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include "offset.h"

using namespace std;

DWORD GetModuleBaseAddress(DWORD pId, const wchar_t* moduleName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, moduleName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

int main()
{
	HWND hWnd = FindWindow(NULL, L"AssaultCube");
	if (!hWnd)
	{
		cout << "프로세스를 찾지 못했습니다. 다시 시도하세요" << endl;
		system("pause");
		return 0;
	}
	else
	{
		DWORD targetProcess = GetWindowThreadProcessId(hWnd, &procID);
		if (!targetProcess)
		{
			cout << "PID를 가져오지 못했습니다. 다시 시도하세요" << endl;
			system("pause");
			return 0;
		}
		else
		{
			cout << "프로세스를 찾았습니다 !! " << endl;
			HANDLE hAndle = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);
			BASE_ADDR = GetModuleBaseAddress(procID, L"ac_client.exe");
			PLAYER_BASE = BASE_ADDR + 0x0017E0A8;
			cout << "[NUMPAD 1] : HP 999" << endl <<  "[NUMPAD 2] : 탄약무한" << endl << "[NUMPAD 3] : 노딜레이" << endl << "[NUMPAD4] : 총기반동제거" << endl;

			while (true)
			{
				Sleep(100);
				if (GetAsyncKeyState(VK_NUMPAD1))
				{
					ReadProcessMemory(hAndle, (LPVOID*)PLAYER_BASE, &pAddress, sizeof(pAddress), NULL);
					pAddress += 0xEC;
					newValue = 999;
					WriteProcessMemory(hAndle, (LPVOID*)pAddress, &newValue, sizeof(newValue), NULL);
				}

				if (GetAsyncKeyState(VK_NUMPAD2))
				{
					/*ReadProcessMemory(hAndle, (LPVOID*)PLAYER_BASE, &pAddress, sizeof(pAddress), NULL);
					pAddress += 0x140;
					newValue = 999;
					WriteProcessMemory(hAndle, (LPVOID*)pAddress, &newValue, sizeof(newValue), NULL);*/
					DWORD oldProtect;
					VirtualProtectEx(hAndle, (BYTE*)(BASE_ADDR + 0xC73EF), 2, PAGE_EXECUTE_READWRITE, &oldProtect);
					WriteProcessMemory(hAndle, (BYTE*)(BASE_ADDR + 0xC73EF), (BYTE*)"\x90\x90", 2, NULL);
					VirtualProtectEx(hAndle, (BYTE*)(BASE_ADDR + 0xC73EF), 2, oldProtect, &oldProtect);
				}

				if (GetAsyncKeyState(VK_NUMPAD3))
				{
					ReadProcessMemory(hAndle, (LPVOID*)PLAYER_BASE, &pAddress, sizeof(pAddress), NULL);
					pAddress += 0x164;
					newValue = 0;
					WriteProcessMemory(hAndle, (LPVOID*)pAddress, &newValue, sizeof(newValue), NULL);
				}

				if (GetAsyncKeyState(VK_NUMPAD4))
				{
					DWORD oldProtect;
					VirtualProtectEx(hAndle, (BYTE*)(BASE_ADDR + 0xC8BA0), 3, PAGE_EXECUTE_READWRITE, &oldProtect);
					WriteProcessMemory(hAndle, (BYTE*)(BASE_ADDR + 0xC8BA0), (BYTE*)"\xC2\x08\x00", 3, NULL);
					VirtualProtectEx(hAndle, (BYTE*)(BASE_ADDR + 0xC8BA0), 3, oldProtect, &oldProtect);
				}
			}
		}
	}
	system("pause");
}
