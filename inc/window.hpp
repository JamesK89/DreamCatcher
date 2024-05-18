#pragma once
#ifndef _INCLUDE_DREAMCATCHER_WINDOW_H_
#define _INCLUDE_DREAMCATCHER_WINDOW_H_

#include <dreamcatcher.hpp>

void __cdecl DF_InitSurface(DF_Surface*);
void __cdecl DF_FreeSurface(DF_Surface*);
void __cdecl DF_CreateMessageWindow(DF_Window**);
void __cdecl DF_CreateGameWindow(const char*, DF_Window**);

#endif
