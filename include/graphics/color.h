#pragma once
#include <stdint.h>

typedef struct
{
    uint8_t b, g, r, a;
} __attribute__((packed)) Color;

static const Color COLOR_TRANSPARENT = (Color){ 0xFF, 0xFF, 0xFF, 0x00 };
static const Color COLOR_BLACK       = (Color){ 0x00, 0x00, 0x00, 0xFF };
static const Color COLOR_WHITE       = (Color){ 0xFF, 0xFF, 0xFF, 0x00 };