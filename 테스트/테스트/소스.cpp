#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleTitle(TEXT("�׽�Ʈ"));
	HMODULE hmodule = LoadLibrary(L"AntiCheatSolution.dll");
	if (hmodule == NULL)
		cout << "�ε� ����" << endl;
	else
		cout << "�ε� ���� !!" << endl;

	getchar();
}