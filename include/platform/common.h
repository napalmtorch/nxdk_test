#pragma once
#include <hal/video.h>
#include <hal/xbox.h>
#include <hal/debug.h>
#include <pbkit/pbkit.h>
#include <xboxkrnl/xboxkrnl.h>
#include <windows.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>

#define MASK(mask, val) (((val) << (__builtin_ffs(mask)-1)) & (mask))