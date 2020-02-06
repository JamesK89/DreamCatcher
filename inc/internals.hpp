#pragma once
#ifndef _INCLUDE_DREAMCATCHER_INTERNALS_H_
#define _INCLUDE_DREAMCATCHER_INTERNALS_H_

#include <dreamcatcher.hpp>

#define DF_INTERNAL_FUNCTION_DECLARE(convention, retType, name, ...) \
	typedef retType (convention *DF_INTERNAL_FUNC_PTR_##name)( __VA_ARGS__ ); \
	extern DF_INTERNAL_FUNC_PTR_##name name;

#define DF_INTERNAL_FUNCTION_ADDRESS_IN_(name, address) \
	DF_INTERNAL_FUNC_PTR_##name name = ((DF_INTERNAL_FUNC_PTR_##name) address );

#if TITANIC
#define DF_INTERNAL_FUNCTION_ADDRESS_IN_TITANIC(name, address) \
	DF_INTERNAL_FUNCTION_ADDRESS_IN_(name, address)

#define DF_INTERNAL_FUNCTION_ADDRESS_IN_LUNICUS(name, address) \

#define DF_INTERNAL_FUNCTION_ADDRESS_IN_DUST(name, address) \

#elif LUNICUS
#define DF_INTERNAL_FUNCTION_ADDRESS_IN_TITANIC(name, address) \

#define DF_INTERNAL_FUNCTION_ADDRESS_IN_LUNICUS(name, address) \
	DF_INTERNAL_FUNCTION_ADDRESS_IN_(name, address)

#define DF_INTERNAL_FUNCTION_ADDRESS_IN_DUST(name, address) \

#else
#define DF_INTERNAL_FUNCTION_ADDRESS_IN_TITANIC(name, address) \

#define DF_INTERNAL_FUNCTION_ADDRESS_IN_LUNICUS(name, address) \


#define DF_INTERNAL_FUNCTION_ADDRESS_IN_DUST(name, address) \
	DF_INTERNAL_FUNCTION_ADDRESS_IN_(name, address)

#endif

DF_INTERNAL_FUNCTION_DECLARE(WINAPI, int, DF_WinMain, HINSTANCE, HINSTANCE, LPSTR, int);

// Run an iteration of a global Windows message pump
DF_INTERNAL_FUNCTION_DECLARE(__cdecl, void, DF_ProcessMessages, void);

// Maps an internal path name to a physical file e.g. "appl:local:movies:intro.mov" to "C:\DUST\MOVIES\INTRO.MOV"
// Since the game was cross-platform between Windows 3.x and Mac OS (before OS X) I'm guess that this is a platform
// neutral way to describe the game's data structure. "appl:" seems to refer to the root of this data structure and
// might be either a reference to the Apple platform or to the game's programmer Bill Appleton.
DF_INTERNAL_FUNCTION_DECLARE(__cdecl, short, DF_ResolveFilePath, const char*, char*);

// I haven't used this yet but it seems to read a fixed chunk of data into a buffer from a given file.
DF_INTERNAL_FUNCTION_DECLARE(__cdecl, void, DF_ReadFileChunk, HANDLE*, void*);

// Seems to retrieve a string from a table.
// The strings seem to be an array of 256-character blocks and initially all of them
// are "appl:" but later are updated with values such as; "appl:local:movies", "appl:local:inven" and so forth.
DF_INTERNAL_FUNCTION_DECLARE(__cdecl, void, DF_GetTableString, WORD, char*);

DF_INTERNAL_FUNCTION_DECLARE(__cdecl, void, DF_FatalError, WORD, WORD);

#endif