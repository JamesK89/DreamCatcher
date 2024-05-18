#include <dreamcatcher.hpp>
#include <window.hpp>
#include <internals.hpp>

void __cdecl DF_InitSurface(
	DF_Surface* pSurface)
{
#if DEBUG
	printf("DF_InitSurface\n");
#endif

	ZeroMemory(pSurface, sizeof(DF_Bitmap));

	pSurface->backcolindex = 0xFF;
	pSurface->backcol = 0xFFFFFFFF;
	pSurface->fontsize = 12;
	pSurface->patsolid = 1;
	pSurface->pensize = 1;
	*((DWORD*)&pSurface->pat[0]) = 0xFFFFFFFF;
	*((DWORD*)&pSurface->pat[4]) = 0xFFFFFFFF;
}

BEGIN_CALL_PATCHES(DF_InitSurface)
	PATCH_CALL_IN_DUST(0x0042828C)
	PATCH_CALL_IN_DUST(0x0042DDC1)
	PATCH_CALL_IN_DUST(0x0042FEC2)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(0x0042D740, DF_InitSurface)

void __cdecl DF_FreeSurface(
	DF_Surface* pSurface)
{
#if DEBUG
	printf("DF_FreeSurface\n");
#endif

	if (pSurface)
	{
		if (pSurface->font)
		{
			DeleteObject(pSurface->font);
		}

		if (pSurface->pen)
		{
			DeleteObject(pSurface->pen);
		}

		if (pSurface->backbrush)
		{
			DeleteObject(pSurface->backbrush);
		}

		if (pSurface->brush)
		{
			DeleteObject(pSurface->brush);
		}

		ZeroMemory(pSurface, sizeof(DF_Surface));
	}
}

BEGIN_CALL_PATCHES(DF_FreeSurface)
	PATCH_CALL_IN_DUST(0x0042DDDA)
	PATCH_CALL_IN_DUST(0x0042FE3D)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(0x0042D7B0, DF_FreeSurface)

void __cdecl DF_CreateMessageWindow(
	DF_Window** wnd)
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

		DF_Window* pWnd =
			(DF_Window*)GlobalAlloc(
				GMEM_FIXED, sizeof(DF_Window));

		if (pWnd)
		{
			pWnd->hwnd = handle;
			pWnd->hdc = GetDC(pWnd->hwnd);
			DF_InitSurface(&pWnd->surface);
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
	DF_Window** wnd)
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

		DF_Window* pWnd =
			(DF_Window*)GlobalAlloc(
				GMEM_FIXED, sizeof(DF_Window));

		if (pWnd)
		{
			pWnd->hwnd = handle;
			pWnd->hdc = GetDC(pWnd->hwnd);
			DF_InitSurface(&pWnd->surface);
			Global.windows[*Global.numWindows] = pWnd;
			Global.unknownWindowValues[*Global.numWindows] = 0;
			*Global.numWindows += 1;

			*wnd = pWnd;

			if (!*Global.mainWindowHandle)
			{
				*Global.mainWindowHandle = handle;
			}
		}

#if 1
		HWND hConsole = GetConsoleWindow();
		if (hConsole)
		{
			//SetParent(hConsole, handle);
			SetWindowPos(hConsole, 
				HWND_TOPMOST,
				0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE);
		}
#endif

		printf("Created game window!\n");
	}
}

BEGIN_CALL_PATCHES(DF_CreateGameWindow)
	PATCH_CALL_IN_DUST(0x00417A47)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042FE70, DF_CreateGameWindow)