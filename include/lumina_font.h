/**
 * @file:      lumina_font.h
 *
 * @date:      17 August 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#pragma once

#include "lumina_color.h"
#include <stdint.h>

/**
 * @typedef lumina_font_glyph_lut_entry_t
 * @brief Describes an entry in the glyph lookup table
 */
typedef uint16_t lumina_font_glyph_lut_entry_t;

/**
 * @enum lumina_font_indexing_mode_t
 * @brief Describes the indexing mode of the font, whether to use ASCII or Unicode
 */
typedef enum lumina_font_indexing_mode_t
{
    LUMINA_FONT_INDEXING_MODE_ASCII,
    LUMINA_FONT_INDEXING_MODE_UNICODE
} lumina_font_indexing_mode_t;

/**
 * @struct lumina_font_glyph_metadata_t
 * @brief Describes the metadata of a glyph
 *
 * @var width The width of the glyph's bitmap
 * @var height The height of the glyph's bitmap
 * @var advance The advance of the glyph
 * @var y_offset The y offset of the glyph
 * @var bitmap_index The index of the bitmap in the font
 */
typedef struct lumina_font_glyph_metadata_t
{
    const uint8_t width;
    const uint8_t height;
    const uint8_t advance;
    const uint8_t y_offset;
    const uint32_t bitmap_index;
} lumina_font_glyph_metadata_t;

/**
 * @struct lumina_font_t
 * @brief Describes a font
 *
 * @var bpp The bits per pixel of the font
 * @var first_valid_index The first valid index of the font. In ASCII mode, this is the ASCII value of the first character.
 * @var last_valid_index The last valid index of the font. In ASCII mode, this is the ASCII value of the last character.
 * @var glyph_lut The lookup table of the font
 * @var glyph_bitmap The bitmap of the font
 * @var glyph_metadata The metadata of the font
 * @var indexing_mode The indexing mode of the font
 */
typedef struct lumina_font_t
{
    const uint8_t bpp;
    const lumina_font_indexing_mode_t indexing_mode;
    const uint16_t first_valid_index;
    const uint16_t last_valid_index;
    const uint8_t *glyph_bitmap;
    const lumina_font_glyph_lut_entry_t *glyph_lut;
    const lumina_font_glyph_metadata_t *glyph_metadata;
} lumina_font_t;

/**
 * @struct lumina_font_style_t
 * @brief Describes the style of a font
 *
 * @var text_color The color of the text
 * @var background_color The color of the background. When font bpp > 1, this is used for antialiasing and rendering smooth text
 */
typedef struct lumina_font_style_t
{
    lumina_color_t text_color;
    lumina_color_t background_color;
} lumina_font_style_t;

const lumina_font_glyph_metadata_t *lumina_font_get_glyph_metadata_from_character(
    const char character,
    const lumina_font_t *const font
);
