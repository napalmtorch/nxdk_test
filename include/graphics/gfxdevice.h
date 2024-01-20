#pragma once
#include "platform/common.h"
#include "graphics/color.h"
#include "math/point.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

#define GfxBegin() (pb_begin())
#define GfxEnd(p) (pb_end(p))

void GfxInit();
void GfxInitShader();
void GfxClear(Color color);
void GfxDisplay();
void GfxToggleVSync(bool enabled);

void GfxSetConstant(uint32_t reg, size_t reg_count, const void* data);
void GfxSetAttributePointer(uint32_t index, uint32_t fmt, uint32_t sz, uint32_t stride, const void* data);
void GfxDrawArrays(uint32_t mode, int start, int count);

Point GetScreenSize();