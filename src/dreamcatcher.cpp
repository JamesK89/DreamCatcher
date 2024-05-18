#include <dreamcatcher.hpp>
#include <internals.hpp>

extern "C" __declspec(dllexport)
void __cdecl STUB(void)
{
}

void** DF_INTERNAL_ChangeDisplayMode_Addr = 
#if TITANIC
	(void**)NULL;
#elif LUNICUS
	(void**)NULL;
#else
	(void**)0x004468A8;
#endif

void** DF_INTERNAL_EnumDisplaySettings_Addr = 
#if TITANIC
	(void**)NULL;
#elif LUNICUS
#else
	(void**)0x00444F54;
#endif

void** DF_INTERNAL_ExitWindowsEx_Addr = 
#if TITANIC
	(void**)NULL;
#elif LUNICUS
	(void**)NULL;
#else
	(void**)0x00445370;
#endif

GlobalState Global = {
	NULL,
	NULL,
	NULL,
	NULL
};

MethodInfo* AppendMethodInfo(GlobalState& global, const MethodInfo& info)
{
	MethodInfo* result = new MethodInfo();
	memcpy(result, &info, sizeof(MethodInfo));
	
	result->next = global.pMethodInfoList;
	global.pMethodInfoList = result;

	return result;
}

// Override the entry method in case we need to do
// anything fancier that is not appropriate for DllMain.

int WINAPI DivertedDFWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Global.appInstance = hInstance;
	printf("hInstance: %p\nhPrevInstance: %p\nlpCmdLine: %s\nnCmdShow: %i\n", hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return DF_WinMain(
		hInstance,
		hPrevInstance,
		lpCmdLine,
		nCmdShow);
}

BEGIN_CALL_PATCHES(DivertedDFWinMain)
	PATCH_CALL_IN_DUST(0x0043C279)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x00428130, DivertedDFWinMain);

// Override this function to prevent the game from changing 
// the screen resolution.

void __cdecl DF_Set_Display(int, int, int)
{
	*DF_INTERNAL_ChangeDisplayMode_Addr = (void*)NULL;
	*DF_INTERNAL_EnumDisplaySettings_Addr = (void*)NULL;
	*DF_INTERNAL_ExitWindowsEx_Addr = (void*)NULL;
	return;
}

BEGIN_CALL_PATCHES(DF_Set_Display)
	PATCH_CALL_IN_DUST(0x0042BCF2)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x00429CB0, DF_Set_Display);

// Override this function to prevent the game
// from asking about changing the display resolution.

int __cdecl DF_Prompt_Display_Change(int unused)
{
	return 0;
}

BEGIN_CALL_PATCHES(DF_Prompt_Display_Change)
	PATCH_CALL_IN_DUST(0x0042B019)
	PATCH_CALL_IN_DUST(0x0042B11C)
	PATCH_CALL_IN_DUST(0x0042B1CF)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042AD60, DF_Prompt_Display_Change);

// Override this function to prevent the game from
// putting itself into a pause state when the game
// window loses focus. (This makes the game easier to debug)

void __cdecl DF_Set_Pause(int pause)
{
	return;
}

BEGIN_CALL_PATCHES(DF_Set_Pause)
	PATCH_CALL_IN_DUST(0x0042A6AE)
	PATCH_CALL_IN_DUST(0x0042A7A7)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042A130, DF_Set_Pause);

void NOPPatch(void* pDest, size_t numNops)
{
	DWORD OldProt;
	char* ptr = (char*)pDest;

	VirtualProtect(pDest, 5, PAGE_EXECUTE_READWRITE, &OldProt);

	for (size_t i = 0; i < numNops; i++)
	{
		*ptr++ = (char)0x90;
	}

	VirtualProtect(pDest, 5, OldProt, &OldProt);
}

// http://www.rohitab.com/discuss/topic/35537-cc-reverse-engineering-tutorial-for-newbies/
void CallPatch(const void* pDest, void* pSrc) {

	DWORD OldProt;

	VirtualProtect(pSrc, 5, PAGE_EXECUTE_READWRITE, &OldProt);

	*(char*)pSrc = (char)0xE8;

	*(DWORD*)((DWORD)pSrc + 1) = (DWORD)pDest - (DWORD)pSrc - 5;

	VirtualProtect(pSrc, 5, OldProt, &OldProt);
}

void PatchCalls(
	const void** addresses,
	const void* newCall,
	int* count)
{
	const void** current = addresses;

	while (current && *current)
	{
		CallPatch(newCall, (void*)*current);

		if (count)
		{
			*count += 1;
		}

		current++;
	}
}

void Patch(GlobalState& global)
{
	int count = 0;

	printf("Patching...\n");

	MethodInfo* pInfo = global.pMethodInfoList;

	while (pInfo)
	{
		int thisCount = 0;

		printf("\t%s...\t", pInfo->methodName);

		PatchCalls(
			pInfo->callAddresses,
			pInfo->newAddress,
			&thisCount);

		printf("%i\n", thisCount);

		count += thisCount;
		pInfo = pInfo->next;
	}

	printf("Patched %i calls.\n", count);
}

void Unpatch(GlobalState& global)
{
	int count = 0;

	printf("Upatching...\n");

	MethodInfo* pInfo = global.pMethodInfoList;

	while (pInfo)
	{
		printf("\t%s\n", pInfo->methodName);
		PatchCalls(
			pInfo->callAddresses,
			pInfo->oldAddress,
			&count);
		
		MethodInfo* pOldInfo = pInfo;
		pInfo = pInfo->next;
		delete pOldInfo;
	}

	printf("Upatched %i calls.\n", count);
}

// Write NOP to a division instruction that
// causes a divide-by-zero exception on modern systems.

void PatchDivideCrash()
{
#if TITANIC
#elif LUNICUS
#else
	NOPPatch((void*)0x0042B459, 2);
#endif
}

// Write NOP to some calls to SetSysColor
// so we don't end up with messed up colors
// everywhere (e.g. black text boxes with black text).

void PatchSysColorCalls()
{
#if TITANIC
#elif LUNICUS
#else
	NOPPatch((void*)0x0042922D, 17);
	NOPPatch((void*)0x004291B0, 17);
#endif
}

BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
)
{
	if (lpvReserved)
	{
		if (fdwReason == DLL_PROCESS_ATTACH || fdwReason == DLL_THREAD_ATTACH)
		{
			Global.dllInstance = hinstDLL;

			Global.mainWindowHandle = (HWND*)WINDOW_MAIN_HANDLE_ADDR;
			Global.numWindows = (DWORD*)WINDOW_NUM_ADDR;
			Global.windows = (DF_Window**)WINDOW_STRUCT_ADDR;
			Global.unknownWindowValues = (DWORD**)WINDOW_UNKNOWN_ADDR;

			AllocConsole();
			freopen_s(&Global.console, "CONOUT$", "w", stdout);

			PatchSysColorCalls();
			PatchDivideCrash();

			Patch(Global);

			printf("Ready!\n");
		}
		else if (fdwReason == DLL_PROCESS_DETACH || fdwReason == DLL_THREAD_DETACH)
		{
			Unpatch(Global);

			if (Global.console)
			{
				fclose(Global.console);
				Global.console = NULL;
			}

			FreeConsole();
		}
	}

	return TRUE;
}