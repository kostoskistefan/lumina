/**
 * @file:      lumina_text.c
 *
 * @date:      17 August 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#include "graphics/lumina_text.h"
#include "lumina_math.h"

extern void lumina_pixel_set(const uint16_t x, const uint16_t y, const lumina_color_t color);

void lumina_graphics_render_glyph(
    const lumina_font_glyph_metadata_t *glyph_metadata,
    const lumina_point_t position,
    const lumina_font_t *font,
    const lumina_font_style_t style
)
{
    // Calculate how many pixels are stored in each bitmap byte
    const uint8_t pixels_per_byte = 8 / font->bpp;

    // Calculate the bit shift amount needed to access the most significant pixel in a bitmap byte.
    // For example, if there are 4 pixels per byte and each pixel is represented by 2 bits (bpp = 2),
    // the most significant pixel is located at the position (4 - 1) * 2 = 6, meaning the bits need to be shifted
    // right by 6 positions to align the most significant pixel with the least significant bit (LSB) position.
    const uint8_t most_significant_pixel_shift_amount = (pixels_per_byte - 1) * font->bpp;

    // Calculate the bitmask for extracting a single pixel from a bitmap byte
    const uint8_t pixel_bitmask = (1 << font->bpp) - 1;

    const uint8_t bitmap_row_width = lumina_math_ceil(glyph_metadata->width / (float) pixels_per_byte);

    // Iterate over all the rows in the bitmap
    for (uint16_t row = 0; row < glyph_metadata->height; ++row)
    {
        const uint8_t *glyph_row = &font->glyph_bitmap[glyph_metadata->bitmap_index + row * bitmap_row_width];

        // Iterate over all the bytes in the row
        for (uint16_t byte_column = 0; byte_column < bitmap_row_width; ++byte_column)
        {
            const uint8_t bitmap_byte = glyph_row[byte_column];

            // Process each pixel in the current byte
            for (uint8_t i = 0; i < pixels_per_byte; ++i)
            {
                // Calculate the column position
                uint16_t column = byte_column * pixels_per_byte + i;

                // Ensure we don't process beyond the glyph width
                if (column >= glyph_metadata->width)
                {
                    break;
                }

                // Extract the pixel intensity
                const uint8_t shift_amount = most_significant_pixel_shift_amount - (i * font->bpp);
                const uint8_t pixel_intensity = (bitmap_byte >> shift_amount) & pixel_bitmask;

                // If the pixel intensity is 0, set the background color directly.
                // This avoids unnecessary division and color interpolation
                if (pixel_intensity == 0)
                {
                    // lumina_pixel_set(
                    //     position.x + column,
                    //     position.y + glyph_metadata->y_offset + row,
                    //     style.background_color
                    // );

                    continue;
                }

                // If the pixel intensity is max, set the text color directly.
                // This avoids unnecessary division and color interpolation
                if (pixel_intensity == pixel_bitmask)
                {
                    lumina_pixel_set(
                        position.x + column,
                        position.y + glyph_metadata->y_offset + row,
                        style.text_color
                    );

                    continue;
                }

                // Calculate the color interpolation amount
                // This represents how much the text color should be blended with the background color
                const float color_interpolation_amount = ((float) pixel_intensity) / ((float) pixel_bitmask);

                // Interpolate between the background and text colors to get the pixel color
                const lumina_color_t pixel_color =
                    lumina_color_interpolate(
                        style.background_color,
                        style.text_color,
                        color_interpolation_amount
                    );

                // Set the pixel
                lumina_pixel_set(position.x + column, position.y + glyph_metadata->y_offset + row, pixel_color);
            }
        }
    }
}

void lumina_graphics_render_text(
    const char *text,
    const lumina_point_t position,
    const lumina_font_t *font,
    const lumina_font_style_t style
)
{
    // TODO: Check for overflow and screen boundary

    lumina_point_t character_position = position;

    // Iterate over all the characters in the text
    for (uint16_t i = 0; text[i] != '\0'; ++i)
    {
        // Get the metadata of the glyph
        const lumina_font_glyph_metadata_t *glyph_metadata = lumina_font_get_glyph_metadata_from_character(text[i], font);

        // Render the glyph
        lumina_graphics_render_glyph(glyph_metadata, character_position, font, style);

        // Update the position for the next character
        character_position.x += glyph_metadata->advance;
    }
}

uint16_t lumina_graphics_measure_text_width(
    const char *text,
    const lumina_font_t *font
)
{
    uint16_t width = 0;

    for (uint16_t i = 0; text[i] != '\0'; ++i)
    {
        // Get the metadata of the glyph
        const lumina_font_glyph_metadata_t *glyph_metadata = lumina_font_get_glyph_metadata_from_character(text[i], font);

        width += glyph_metadata->advance;
    }

    return width;
}

void lumina_graphics_render_text_aligned(
    const char *text,
    const lumina_point_t position,
    const lumina_font_t *font,
    const lumina_font_style_t style,
    const lumina_text_alignment_t alignment
)
{
    // TODO: Check for overflow and screen boundary

    lumina_point_t adjusted_position = position;

    switch (alignment)
    {
        case LUMINA_TEXT_ALIGNMENT_LEFT:
            lumina_graphics_render_text(text, position, font, style);
            break;

        case LUMINA_TEXT_ALIGNMENT_CENTER:
            adjusted_position.x -= lumina_graphics_measure_text_width(text, font) / 2;
            lumina_graphics_render_text(text, adjusted_position, font, style);
            break;

        case LUMINA_TEXT_ALIGNMENT_RIGHT:
            adjusted_position.x -= lumina_graphics_measure_text_width(text, font);
            lumina_graphics_render_text(text, adjusted_position, font, style);
            break;
    }
}
