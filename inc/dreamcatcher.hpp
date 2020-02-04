#pragma once
#ifndef _INCLUDE_DREAMCATCHER_H_
#define _INCLUDE_DREAMCATCHER_H_

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct unknown_struct_t
{
	DWORD unknown00_x00;
	DWORD unknown01_x04;
	DWORD unknown02_x08;
	DWORD unknown03_x0C;
	DWORD unknown04_x10;
	DWORD unknown05_x14;
	DWORD unknown06_x18;
	DWORD unknown07_x1C;
	DWORD unknown08_x20;
	DWORD unknown11_x24;
	DWORD unknown12_x28;
	DWORD unknown13_x2C;
	DWORD unknown14_x30;
	DWORD unknown15_x34;
	DWORD unknown16_x38;
	DWORD unknown17_x3C;
	DWORD unknown18_x40;
	DWORD unknown19_x44;
	DWORD unknown20_x48;
	DWORD unknown21_x4C;
	DWORD unknown22_x50;
	DWORD unknown23_x54;
} DF_UnknownStruct;

typedef struct window_struct_t
{
	HWND hWnd;
	HDC hDC;
	DF_UnknownStruct unknown;
} DF_WindowInfo;

typedef struct method_info_t
{
	const char* methodName;
	const void** callAddresses;
	const void* newAddress;
	const void* oldAddress;
	struct method_info_t* next;
} MethodInfo;

typedef struct global_state_t
{
	HINSTANCE appInstance;
	HINSTANCE dllInstance;

	FILE* console;
	
	HWND* mainWindowHandle;
	DF_WindowInfo** windows;
	DWORD* numWindows;
	DWORD** unknownWindowValues;

	MethodInfo* pMethodInfoList;
} GlobalState;

extern GlobalState Global;

#if TITANIC
#elif LUNICUS
#else
#	define WINDOW_STRUCT_ADDR		(void*)0x0045A6D0
#	define WINDOW_NUM_ADDR			(void*)0x0045A67C
#	define WINDOW_UNKNOWN_ADDR		(void*)0x0045A200
#	define WINDOW_MAIN_HANDLE_ADDR	(void*)0x0045A178
#endif

#define BEGIN_CALL_PATCHES(name) \
	const void* name##_CALL_ADDRESSES[] = {

#define PATCH_CALL_IN_(address) \
	((void*) address ),

#ifdef TITANIC
#	define PATCH_CALL_IN_TITANIC(address) PATCH_CALL_IN_(address)

#	define PATCH_CALL_IN_LUNICUS(address) \

#	define PATCH_CALL_IN_DUST(address) \

#elif LUNICUS
#	define PATCH_CALL_IN_TITANIC(address) \

#	define PATCH_CALL_IN_LUNICUS(address) PATCH_CALL_IN_(address)

#	define PATCH_CALL_IN_DUST(address) \

#else
#	define PATCH_CALL_IN_TITANIC(address) \

#	define PATCH_CALL_IN_LUNICUS(address) \

#	define PATCH_CALL_IN_DUST(address) PATCH_CALL_IN_(address)
#endif

#define END_CALL_PATCHES \
 (void*)NULL };

#define DECLARE_DF_FUNCTION_IN_(address, name) \
	MethodInfo* name##_METHOD_INFO = \
		AppendMethodInfo( \
		Global, \
		{ \
			#name, \
			&name##_CALL_ADDRESSES[0], \
			(const void*)&##name, \
			(const void*)address, \
			NULL \
		});

#ifdef TITANIC
#	define DECLARE_DF_FUNCTION_IN_TITANIC(address, name) DECLARE_DF_FUNCTION_IN_(address, name)

#	define DECLARE_DF_FUNCTION_IN_LUNICUS(address, name) \

#	define DECLARE_DF_FUNCTION_IN_DUST(address, name) \

#elif LUNICUS
#	define DECLARE_DF_FUNCTION_IN_TITANIC(address, name) \

#	define DECLARE_DF_FUNCTION_IN_LUNICUS(address, name) DECLARE_DF_FUNCTION_IN_(address, name)

#	define DECLARE_DF_FUNCTION_IN_DUST(address, name) \

#else
#	define DECLARE_DF_FUNCTION_IN_TITANIC(address, name) \

#	define DECLARE_DF_FUNCTION_IN_LUNICUS(address, name) \

#	define DECLARE_DF_FUNCTION_IN_DUST(address, name) DECLARE_DF_FUNCTION_IN_(address, name)
#endif

MethodInfo* AppendMethodInfo(GlobalState& global, const MethodInfo& info);

#endif