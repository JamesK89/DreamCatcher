#ifndef _INCLUDE_DREAMCATCHER_GRAPHICS_HPP_
#define _INCLUDE_DREAMCATCHER_GRAPHICS_HPP_

#include <dreamcatcher.hpp>

DWORD __cdecl DF_InitializeGdiFunctions(void);

void __cdecl DF_InitSurface(DF_Surface*);
void __cdecl DF_FreeSurface(DF_Surface*);

HBITMAP __cdecl DF_CreateBitmapHelper(HDC, BITMAPINFO*, void**);
void __cdecl DF_CreateBitmap(DF_Bitmap*, WORD, WORD);

#endif