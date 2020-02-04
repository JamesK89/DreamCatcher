#pragma once
#ifndef _INCLUDE_DREAMCATCHER_WINDOW_H_
#define _INCLUDE_DREAMCATCHER_WINDOW_H_

#include <dreamcatcher.hpp>

void __cdecl DF_InitUnknownStruct(DF_UnknownStruct*);
void __cdecl DF_CreateMessageWindow(DF_WindowInfo**);
void __cdecl DF_CreateGameWindow(const char*, DF_WindowInfo**);

#endif
