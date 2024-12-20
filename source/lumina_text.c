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
    const lumina_uint8_t pixel_bitmask = (1 << font->bits_per_pixel) - 1;
    const lumina_uint16_t pixels_per_byte = 8.0f / font->bits_per_pixel;
    const lumina_uint16_t data_length = (glyph_data->width * glyph_data->height * font->bits_per_pixel) >> 3;
    const lumina_uint8_t *bitmap_start = &font->bitmap[glyph_data->bitmap_index];
    const lumina_uint8_t pixel_chunk_start = (pixels_per_byte - 1) * font->bits_per_pixel;

    lumina_uint16_t row = 0;
    lumina_uint16_t column = 0;

    const lumina_uint16_t glyph_y_offset = y + font->ascent - glyph_data->y_bearing;

    for (lumina_uint16_t i = 0; i < data_length; ++i)
    {
        for (
            lumina_int8_t pixel_chunk_index = pixel_chunk_start;
            pixel_chunk_index >= 0;
            pixel_chunk_index -= font->bits_per_pixel
        )
        {
            const lumina_uint8_t pixel = (bitmap_start[i] >> pixel_chunk_index) & pixel_bitmask;

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

lumina_uint16_t lumina_text_get_width(const lumina_char_t *text, const lumina_font_t *const font)
{
    lumina_uint16_t width = 0;

    lumina_utf8_iterator_t text_iterator = lumina_utf8_iterator_create(text);
    lumina_utf8_unicode_codepoint_t codepoint;

    const lumina_font_glyph_data_t *glyph_data;

    while ((codepoint = lumina_utf8_iterator_next(&text_iterator)) != 0)
    {
        glyph_data = lumina_font_get_glyph_data(font, codepoint);

        if (glyph_data == NULL)
        {
            continue;
        }

        width += glyph_data->advance;
    }

    return width - glyph_data->advance + glyph_data->width - 1;
}

void lumina_render_text(
    const lumina_char_t *text,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_text_alignment_t alignment,
    const lumina_text_style_t *const style
)
{
    lumina_uint16_t pen_x = x;

    switch (alignment)
    {
        case LUMINA_TEXT_ALIGNMENT_LEFT:
            break;

        case LUMINA_TEXT_ALIGNMENT_RIGHT:
            {
                const lumina_uint16_t text_width = lumina_text_get_width(text, style->font);
                pen_x = (text_width > pen_x) ? 0 : pen_x - text_width;
                break;
            }

        case LUMINA_TEXT_ALIGNMENT_CENTER:
            {
                const lumina_uint16_t half_text_width = lumina_text_get_width(text, style->font) / 2;
                pen_x = (half_text_width > pen_x) ? 0 : pen_x - half_text_width;
                break;
            }
    }

    lumina_utf8_iterator_t text_iterator = lumina_utf8_iterator_create(text);
    lumina_utf8_unicode_codepoint_t codepoint;

    while ((codepoint = lumina_utf8_iterator_next(&text_iterator)) != 0)
    {
        const lumina_font_glyph_data_t *const glyph_data = lumina_font_get_glyph_data(style->font, codepoint);

        if (glyph_data == NULL)
        {
            continue;
        }

        lumina_render_glyph(style->font, glyph_data, pen_x, y, style->foreground_color, style->background_color);

        pen_x += glyph_data->advance;
    }
}
