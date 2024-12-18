/**
 * @file:      lumina_font.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_types.h"
#ifndef LUMINA_FONT_H
#define LUMINA_FONT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lumina_utf8.h"

typedef enum lumina_font_character_map_type_t
{
    LUMINA_FONT_CHARACTER_MAP_TYPE_SEQUENTIAL,
    LUMINA_FONT_CHARACTER_MAP_TYPE_SPARSE
} lumina_font_character_map_type_t;

typedef struct lumina_font_glyph_data_t 
{
    const lumina_uint32_t bitmap_index;

    const lumina_uint16_t advance;

    const lumina_uint16_t width;
    const lumina_uint16_t height;

    const lumina_int16_t y_bearing;
} lumina_font_glyph_data_t;

typedef struct lumina_font_character_map_t
{
    const lumina_uint32_t range_start;
    const lumina_uint16_t range_length;

    const lumina_uint16_t glyph_bitmap_start_index;

    const lumina_utf8_unicode_codepoint_t *const unicode_codepoints;
    const lumina_uint16_t unicode_codepoints_count;

    const lumina_font_character_map_type_t type;
} lumina_font_character_map_t;

typedef struct lumina_font_t
{
    const lumina_uint8_t ascent;
    const lumina_uint8_t descent;
    const lumina_uint8_t bits_per_pixel;

    const lumina_uint8_t *const bitmap;
    const lumina_font_glyph_data_t *const glyph_data;

    const lumina_font_character_map_t *const character_maps;
    const lumina_uint16_t character_maps_count;
} lumina_font_t;

const lumina_font_glyph_data_t *lumina_font_get_glyph_data(
    const lumina_font_t *const font,
    const lumina_utf8_unicode_codepoint_t codepoint
);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_FONT_H
