#pragma once
#ifndef _INCLUDE_DREAMCATCHER_FILES_H_
#define _INCLUDE_DREAMCATCHER_FILES_H_

#include "dreamcatcher.hpp"

WORD __cdecl DF_OpenFile(const char*, HANDLE*);
WORD __cdecl DF_CloseFile(HANDLE*);
WORD __cdecl DF_ReadIntoBuffer(HANDLE*, char*, size_t);
WORD __cdecl DF_GetFileSize(HANDLE*, DWORD*);
WORD __cdecl DF_GetFileExists(char*, DWORD*, DWORD*);

#endif