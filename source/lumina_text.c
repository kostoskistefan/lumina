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
#include "lumina_driver.h"
#include <math.h>
#include <stdio.h>

void lumina_render_glyph(
    const lumina_font_t *const font,
    const lumina_font_glyph_data_t *const glyph_data,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    const lumina_uint16_t inverse_bpp = 8.0 / font->bits_per_pixel;
    const lumina_uint16_t pixel_bitmask = (1 << font->bits_per_pixel) - 1;

    const lumina_uint16_t bitmap_size = floor((glyph_data->bounding_box_width * glyph_data->bounding_box_height) / (float) inverse_bpp);

    lumina_uint16_t row = 0;
    lumina_uint16_t column = 0;

    for (lumina_uint16_t i = 0; i < bitmap_size; ++i)
    {
        const lumina_uint8_t glyph_byte = font->bitmap[glyph_data->bitmap_index + i];

        for (lumina_uint16_t j = 0; j < inverse_bpp; ++j)
        {
            const lumina_uint8_t pixel_raw_value = (glyph_byte >> ((inverse_bpp - 1 - j) * font->bits_per_pixel)) & pixel_bitmask;

            if (pixel_raw_value == 0)
            {
                lumina_fill_area(x + column, y + 11 - glyph_data->bounding_box_height + row, 1, 1, background_color);
            }

            else if (pixel_raw_value == pixel_bitmask)
            {
                lumina_fill_area(x + column, y + 11 - glyph_data->bounding_box_height + row, 1, 1, foreground_color);
            }

            else
            {
                lumina_fill_area(
                    x + column,
                    y + 11 - glyph_data->bounding_box_height + row,
                    1,
                    1,
                    lumina_color_mix(
                        background_color,
                        foreground_color,
                        (pixel_raw_value + 1) / ((lumina_float_t) pixel_bitmask + 1)
                    )
                );
            }

            ++column;

            if (column % glyph_data->bounding_box_width == 0)
            {
                column = 0;
                ++row;
            }
        }
    }
}

void lumina_render_text(
    const lumina_char_t *text,
    const lumina_font_t *const font,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    lumina_uint16_t pen_x = x;

    lumina_utf8_iterator_t text_iterator = lumina_utf8_iterator_create(text);
    lumina_utf8_unicode_codepoint_t codepoint;

    while ((codepoint = lumina_utf8_iterator_next(&text_iterator)) != 0)
    {
        const lumina_font_glyph_data_t *const glyph_data = lumina_font_get_glyph_data(font, codepoint);

        if (glyph_data == NULL)
        {
            continue;
        }

        lumina_render_glyph(font, glyph_data, pen_x, y, foreground_color, background_color);

        pen_x += (glyph_data->advance_width >> 4);
    }
}
