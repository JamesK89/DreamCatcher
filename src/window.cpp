#include <dreamcatcher.hpp>
#include <window.hpp>
#include <internals.hpp>

void __cdecl DF_InitUnknownStruct(
	DF_UnknownStruct* pStruct)
{
	pStruct->unknown00_x00 = 0;
	pStruct->unknown01_x04 = 0;
	pStruct->unknown02_x08 = 0;
	pStruct->unknown03_x0C = 0;
	pStruct->unknown04_x10 = 0;
	pStruct->unknown05_x14 = 0;
	pStruct->unknown06_x18 = 0xFFFFFF;
	pStruct->unknown07_x1C = 0xFF;
	pStruct->unknown08_x20 = 0xFFFFFFFF;
	pStruct->unknown11_x24 = 0xFFFFFFFF;
	pStruct->unknown12_x28 = 1;
	pStruct->unknown13_x2C = 0;
	pStruct->unknown14_x30 = 0;
	pStruct->unknown15_x34 = 0;
	pStruct->unknown16_x38 = 0;
	pStruct->unknown17_x3C = 0x0C;
	pStruct->unknown18_x40 = 0;
	pStruct->unknown19_x44 = 0;
	pStruct->unknown20_x48 = 0;
	pStruct->unknown21_x4C = 1;
	pStruct->unknown22_x50 = 0;
	pStruct->unknown23_x54 = 0;
}

BEGIN_CALL_PATCHES(DF_InitUnknownStruct)
	PATCH_CALL_IN_DUST(0x0042828C)
	PATCH_CALL_IN_DUST(0x0042DDC1)
	PATCH_CALL_IN_DUST(0x0042FEC2)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(0x0042D740, DF_InitUnknownStruct)

void __cdecl DF_CreateMessageWindow(
	DF_WindowInfo** wnd)
{
	if (wnd)
	{
		HWND handle = CreateWindowExA(
			0,						// dwExStyle
			"DFWindow",				// lpClassName
			"Messages",				// lpWindowName
			0x80ca0000,				// dwStyle
			100,					// X
			100,					// Y
			100,					// nWidth
			100,					// nHeight
			NULL,					// hWndParent
			NULL,					// hMenu
			Global.appInstance,		// hInstance
			NULL);					// lpParam

		DF_WindowInfo* pWnd =
			(DF_WindowInfo*)GlobalAlloc(
				GMEM_FIXED, sizeof(DF_WindowInfo));

		if (pWnd)
		{
			pWnd->hWnd = handle;
			pWnd->hDC = GetDC(pWnd->hWnd);
			DF_InitUnknownStruct(&pWnd->unknown);
			Global.windows[*Global.numWindows] = pWnd;
			Global.unknownWindowValues[*Global.numWindows] = 0;
			*Global.numWindows += 1;

			*wnd = pWnd;
		}

		printf("Created messages window!\n");
	}
}

BEGIN_CALL_PATCHES(DF_CreateMessageWindow)
	PATCH_CALL_IN_DUST(0x004193EE)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x00428240, DF_CreateMessageWindow)

void PrintTableString(WORD id)
{
	char str[256];

	memset(str, '\0', sizeof(str));
	DF_GetTableString(id, str);

	printf("Table String: %.*s\n", str[0], &str[1]);
}

void __cdecl DF_CreateGameWindow(
	const char* unusedPrefixedString,
	DF_WindowInfo** wnd)
{
	if (wnd)
	{
		HWND handle = CreateWindowExA(
			0,						// dwExStyle
			"DFWindow",				// lpClassName
			(const char*)0x0045A130,// lpWindowName
			0x80080000,				// dwStyle
			100,					// X
			100,					// Y
			300,					// nWidth
			200,					// nHeight
			NULL,					// hWndParent
			NULL,					// hMenu
			Global.appInstance,	// hInstance
			NULL);					// lpParam

		DF_WindowInfo* pWnd =
			(DF_WindowInfo*)GlobalAlloc(
				GMEM_FIXED, sizeof(DF_WindowInfo));

		if (pWnd)
		{
			pWnd->hWnd = handle;
			pWnd->hDC = GetDC(pWnd->hWnd);
			DF_InitUnknownStruct(&pWnd->unknown);
			Global.windows[*Global.numWindows] = pWnd;
			Global.unknownWindowValues[*Global.numWindows] = 0;
			*Global.numWindows += 1;

			*wnd = pWnd;

			if (!*Global.mainWindowHandle)
			{
				*Global.mainWindowHandle = handle;
			}
		}

		printf("Created game window!\n");
	}
}

BEGIN_CALL_PATCHES(DF_CreateGameWindow)
	PATCH_CALL_IN_DUST(0x00417A47)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042FE70, DF_CreateGameWindow)