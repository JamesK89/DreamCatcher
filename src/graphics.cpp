#include <graphics.hpp>

DWORD __cdecl DF_InitializeGdiFunctions(
	void)
{
	if (!*Global.isOSBuildNumberTwo)
	{
		*Global.isWinGFuncPtrAcquired = 0;
		*Global.hGdi = LoadLibrary("GDI32.DLL");

		if (*Global.hGdi)
		{
			*Global.gdi32CreateDIBSection = (LpfnGdi32CreateDIBSection)GetProcAddress(*Global.hGdi, "CreateDIBSection");
			*Global.gdi32SetDIBColorTable = (LpfnGdi32SetDIBColorTable)GetProcAddress(*Global.hGdi, "SetDIBColorTable");

			if (*Global.gdi32CreateDIBSection && *Global.gdi32SetDIBColorTable)
			{
				return 1;
			}
		}
	}

	*Global.hGdi = LoadLibrary("WING32.DLL");

	if (!*Global.hGdi)
	{
		return 0;
	}

	*Global.win32CreateBitmap = (LpfnWin32CreateBitmap)GetProcAddress(*Global.hGdi, "WinGCreateBitmap");
	*Global.win32CreateDC = (LpfnWin32CreateDC)GetProcAddress(*Global.hGdi, "WinGCreateDC");
	*Global.win32SetDIBColorTable = (LpfnWin32SetDIBColorTable)GetProcAddress(*Global.hGdi, "WinGSetDIBColorTable");
	*Global.win32BitBlt = (LpfnWin32BitBlt)GetProcAddress(*Global.hGdi, "WinGBitBlt");

	if (*Global.win32CreateBitmap && *Global.win32CreateDC && *Global.win32SetDIBColorTable && *Global.win32BitBlt)
	{
		*Global.isWinGFuncPtrAcquired = 1;
		return 1;
	}

	return 0;
}

BEGIN_CALL_PATCHES(DF_InitializeGdiFunctions)
	PATCH_CALL_IN_DUST(0x0042BE2C)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(0x00428CE0, DF_InitializeGdiFunctions)

void __cdecl DF_InitSurface(
	DF_Surface* pSurface)
{
#if DEBUG
	printf("DF_InitSurface\n");
#endif

	ZeroMemory(pSurface, sizeof(DF_Surface));

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


HBITMAP __cdecl DF_CreateBitmapHelper(
	HDC hdc,
	BITMAPINFO* bmi,
	void** bits)
{
#if DEBUG
	printf("DF_CreateBitmapHelper\n");
#endif

	if (*Global.isWinGFuncPtrAcquired)
	{
		return (*Global.win32CreateBitmap)(hdc, bmi, bits);
	}

	return (*Global.gdi32CreateDIBSection)(hdc, bmi, 0, bits, 0, 0);
}

BEGIN_CALL_PATCHES(DF_CreateBitmapHelper)
	PATCH_CALL_IN_DUST(0x00428C50)
	PATCH_CALL_IN_DUST(0x0042DDAE)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(0x00428E30, DF_CreateBitmapHelper)

void __cdecl DF_CreateBitmap(
	DF_Bitmap* pBitmap,
	WORD rowBytes,
	WORD height)
{
#if DEBUG
	printf("DF_CreateBitmap\n");
#endif

	if (rowBytes & 3)
	{
		rowBytes = (rowBytes - (rowBytes & 3) + 4);
	}

	Global.clutbmih->bmiHeader.biWidth = rowBytes;
	Global.clutbmih->bmiHeader.biHeight = -height;

	pBitmap->rowbytes = rowBytes;
	pBitmap->height = height;
	pBitmap->hbm = DF_CreateBitmapHelper(*Global.deviceContext, Global.clutbmih, (void**)&pBitmap->baseaddr);

	DF_InitSurface(&pBitmap->s);
}

BEGIN_CALL_PATCHES(DF_CreateBitmap)
	PATCH_CALL_IN_DUST(0x0040321D)
	PATCH_CALL_IN_DUST(0x004057B2)
	PATCH_CALL_IN_DUST(0x004057C9)
	PATCH_CALL_IN_DUST(0x00405A2E)
	PATCH_CALL_IN_DUST(0x0041CAA1)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(0x0042DD60, DF_CreateBitmap)