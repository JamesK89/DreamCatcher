#pragma once
#ifndef _INCLUDE_DREAMCATCHER_STRINGS_H_
#define _INCLUDE_DREAMCATCHER_STRINGS_H_

#include <dreamcatcher.hpp>

// Note about strings:
//  The DreamFactory engine seems to use what I call "prefixed" strings.
//  These are typically non-null terminated and the first character contains
//  the length of the string as determined by DF_SetStringLength.
//  Consider:
//        H  E  L  L  O
//  ┌» 05 48 45 4C 4C 4F
//  └ This refers to the fact that "HELLO" is five characters long.

// Copies one prefixed string from one buffer to another.
void __cdecl DF_CopyString(char*, char*);

// Determines the length of a prefixed string and sets the
// length in the prefix.
char* __cdecl DF_SetStringLength(char*);

extern char* DF_INTERNAL_CharacterTable;

// Seems to check if two prefixed strings are equal in terms of
// printable characters using the DF_INTERNAL_CharacterTable array.
WORD __cdecl DF_StringsAreEqual(char*, char*);

// This is a global fixed-size buffer that DF_LoadString utilizes
// and ultimately ends up returning a pointer to.
const size_t DF_INTERNAL_LoadStringBuffer_Length = 384;
extern char* DF_INTERNAL_LoadStringBuffer;

// Actually this just ends up calling the Windows API function LoadStringA.
// It might be a platform abstraction.
const char* __cdecl DF_LoadString(unsigned int);

void __cdecl DF_ConcatStrings(const char* pFrom, char* pTo);

// This takes a standard null terminated C string and shifts the entire string forward by one byte
// and assigns the first byte (which was previously the first character) with the length of the string.
//  Consider before a string before executing this function:
//  H  E  L  L  O
//  48 45 4C 4C 4F 00
// Consider same string after execution:
//        H  E  L  L  O
//  ┌» 05 48 45 4C 4C 4F 00
//  └ This refers to the fact that "HELLO" is five characters long.
void __cdecl DF_ConvertString(char* pStr);

// I am not sure how else to describe this function.
// It seems to check if two given strings are equal up to a certain number of characters.
// I noticed in practice that this function is called repetitively with pHaystack increasing by
// one character with each iteration. So I suspect this function is used to find the first occurance
// of pNeedle within the pHaystack string.
// The return of this function seems to be 0 if successful (a match was found) or 1 if
// the number of characters is zero or there was no match.
char __cdecl DF_StringContainsString(const char* pHaystack, const char* pNeedle, char numChars);

#endif