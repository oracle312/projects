#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleTitle(TEXT("테스트"));
	HMODULE hmodule = LoadLibrary(L"AntiCheatSolution.dll");
	if (hmodule == NULL)
		cout << "로드 실패" << endl;
	else
		cout << "로드 성공 !!" << endl;

	getchar();
}