#include <windows.h>
#include <iostream>

int main()
{

	HANDLE device = CreateFileW(L"\\Device\\VulnDriver", GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	
	if (device == INVALID_HANDLE_VALUE)
		return 0;

	std::printf("Device Opened");

	return 1;
}