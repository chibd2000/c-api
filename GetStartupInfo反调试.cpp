//#include <windows.h>
//#include <stdio.h>
//#pragma comment(linker, "/subsystem:windows /entry:main")
//int main()
//{
//	STARTUPINFO si;
//
//	GetStartupInfo(&si);
//
//	if (
//		(si.dwX != 0) ||
//		(si.dwY != 0) ||
//		(si.dwXCountChars != 0) ||
//		(si.dwYCountChars != 0) ||
//		(si.dwFillAttribute != 0) ||
//		(si.dwXSize != 0) ||
//		(si.dwYSize != 0) ||
//		(si.dwFlags & STARTF_FORCEOFFFEEDBACK)
//		)
//	{
//		MessageBox(NULL, "found debugger!", NULL, 0);
//	}
//	else
//	{
//		MessageBox(NULL, "no found debugger!", NULL, 0);
//	}
//
//	return 0;
//}