#include <system.hpp>

DWORD __cdecl DF_GetOSHasBuildNumberTwo(void)
{
	HMODULE hModule;
	LpfnGetVersionExA getVersionInfo;
	OSVERSIONINFOA osvi;

	hModule = LoadLibrary("kernel32.dll");

	if (!hModule)
	{
		return 0;
	}

	getVersionInfo = (LpfnGetVersionExA)GetProcAddress(hModule, "GetVersionExA");

	if (!getVersionInfo)
	{
		FreeLibrary(hModule);
		return 0;
	}

	(*getVersionInfo)(&osvi);

	FreeModule(hModule);

	return (osvi.dwBuildNumber == 2);
}

BEGIN_CALL_PATCHES(DF_GetOSHasBuildNumberTwo)
	PATCH_CALL_IN_DUST(0x0042B7B6)
	PATCH_CALL_IN_DUST(0x0042B825)
	PATCH_CALL_IN_DUST(0x0042B87D)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(0x0042B720, DF_GetOSHasBuildNumberTwo)