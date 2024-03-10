#pragma once

#include <stdint.h>

typedef struct lumina_font_glyph_data_t
{
    uint8_t width;
    uint8_t y_offset;
    uint16_t length;
    uint32_t glyph_bitmap_index;
} lumina_font_glyph_data_t;

typedef struct lumina_font_t
{
    uint8_t bpp;
    const uint8_t *glyph_bitmap;
    const uint8_t *glyph_data_index;
    const lumina_font_glyph_data_t *glyph_data;
} lumina_font_t;
