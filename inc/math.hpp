#pragma once
#pragma once
#ifndef _INCLUDE_DREAMCATCHER_MATH_H_
#define _INCLUDE_DREAMCATCHER_MATH_H_

#include "dreamcatcher.hpp"

typedef struct wrect_t
{
	WORD top;
	WORD left;
	WORD bottom;
	WORD right;
} WRECT;

typedef struct wpoint_t
{
	WORD y;
	WORD x;
} WPOINT;

#endif
