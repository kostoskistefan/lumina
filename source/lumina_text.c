/**
 * @file:      lumina_text.c
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_text.h"
#include "lumina_utf8.h"
#include "lumina_math.h"
#include "lumina_driver.h"
#include <stddef.h>

void lumina_text_glyph_render(
    const lumina_font_t *const font,
    const lumina_font_glyph_data_t *const glyph_data,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    const lumina_uint8_t pixel_bitmask = (1 << font->bits_per_pixel) - 1;
    const lumina_uint16_t pixels_per_byte = 8.0f / font->bits_per_pixel;
    const lumina_uint16_t glyph_bitmap_length = lumina_math_ceil((glyph_data->width * glyph_data->height * font->bits_per_pixel) / 8.0f);
    const lumina_uint8_t *glyph_bitmap = &font->bitmap[glyph_data->bitmap_index];
    const lumina_uint8_t pixel_chunk_start = (pixels_per_byte - 1) * font->bits_per_pixel;

    lumina_uint16_t row = 0;
    lumina_uint16_t column = 0;

    const lumina_uint16_t glyph_y_offset = y + font->ascent - glyph_data->y_bearing;

    for (lumina_uint16_t i = 0; i < glyph_bitmap_length; ++i)
    {
        for (
            lumina_int8_t pixel_chunk_index = pixel_chunk_start;
            pixel_chunk_index >= 0;
            pixel_chunk_index -= font->bits_per_pixel
        )
        {
            const lumina_uint8_t pixel = (glyph_bitmap[i] >> pixel_chunk_index) & pixel_bitmask;

            if (pixel != 0)
            {
                lumina_fill_area(
                    x + column,
                    glyph_y_offset + row,
                    1,
                    1,
                    lumina_color_mix(
                        background_color,
                        foreground_color,
                        pixel / (float) pixel_bitmask
                    )
                );
            }

            ++column;

            if (column == glyph_data->width)
            {
                ++row;
                column = 0;
            }

            if (row == glyph_data->height)
            {
                break;
            }
        }
    }
}

static inline lumina_uint16_t lumina_text_get_alignment_offset(
    const lumina_char_t *const text,
    const lumina_font_t *const font,
    const lumina_text_alignment_t alignment
)
{
    switch (alignment)
    {
        case LUMINA_TEXT_ALIGNMENT_RIGHT:
            return lumina_text_get_width(text, font);

        case LUMINA_TEXT_ALIGNMENT_CENTER:
            return lumina_text_get_width(text, font) >> 1;

        default:
            return 0;
    }
}

lumina_uint16_t lumina_text_get_width(const lumina_char_t *text, const lumina_font_t *const font)
{
    if (text == NULL || text[0] == '\0' || font == NULL)
    {
        return 0;
    }

    lumina_uint16_t width = 0;

    lumina_utf8_iterator_t text_iterator = lumina_utf8_iterator_create(text);
    lumina_utf8_unicode_codepoint_t codepoint;

    const lumina_font_glyph_data_t *glyph_data = NULL;

    while ((codepoint = lumina_utf8_iterator_next(&text_iterator)) != 0)
    {
        glyph_data = lumina_font_get_glyph_data(font, codepoint);

        if (glyph_data == NULL)
        {
            continue;
        }

        width += glyph_data->advance;
    }

    if (glyph_data == NULL)
    {
        return width;
    }

    return width - glyph_data->advance + glyph_data->width;
}

void lumina_text_render(
    const lumina_char_t *text,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_text_alignment_t alignment,
    const lumina_font_t *const font,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    if (text == NULL || text[0] == '\0' || font == NULL)
    {
        return;
    }

    lumina_uint16_t pen_x = lumina_math_max(0,  x - lumina_text_get_alignment_offset(text, font, alignment));

    lumina_utf8_iterator_t text_iterator = lumina_utf8_iterator_create(text);
    lumina_utf8_unicode_codepoint_t codepoint;

    while ((codepoint = lumina_utf8_iterator_next(&text_iterator)) != 0)
    {
        const lumina_font_glyph_data_t *const glyph_data = lumina_font_get_glyph_data(font, codepoint);

        if (glyph_data == NULL)
        {
            continue;
        }

        lumina_text_glyph_render(font, glyph_data, pen_x, y, foreground_color, background_color);

        pen_x += glyph_data->advance;
    }
}