#pragma once
#ifndef _INCLUDE_DREAMCATCHER_H_
#define _INCLUDE_DREAMCATCHER_H_

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "types.hpp"

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