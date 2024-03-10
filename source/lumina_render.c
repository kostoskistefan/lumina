#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lumina_render.h"
#include "lumina_math.h"
#include "lumina_font.h"
#include "lumina_color.h"
#include "lumina_style.h"

extern void lumina_set_pixel(const uint16_t x, const uint16_t y, const lumina_color_t color);
extern lumina_color_t lumina_get_pixel(const uint16_t x, const uint16_t y);

lumina_style_t _lumina_style = {
    .font = NULL,
    .line_color = 0xffffff,
    .fill_color = 0x000000,
    .compositing_color_interior = 0x000000,
    .compositing_color_exterior = 0x000000,
    .compositing_mode = LUMINA_STYLE_COMPOSITING_MODE_AUTO
};

void lumina_render_vertical_line(const uint16_t x, const uint16_t y, const uint16_t length)
{
    for (uint16_t row = y; row < y + length; ++row)
    {
        lumina_set_pixel(x, row, _lumina_style.line_color);
    }
}

void lumina_render_horizontal_line(const uint16_t x, const uint16_t y, const uint16_t length)
{
    for (uint16_t column = x; column < x + length; ++column)
    {
        lumina_set_pixel(column, y, _lumina_style.line_color);
    }
}

static inline void lumina_aux_render_circle_quadrants_outline(
    const uint16_t x,
    const uint16_t y,
    const uint16_t radius,
    const int32_t row_start,
    const int32_t row_end,
    const int32_t column_start,
    const int32_t column_end
)
{
    for (int32_t row = row_start; row <= row_end; ++row)
    {
        const int32_t row_squared = row * row;

        for (int32_t column = column_start; column <= column_end; ++column)
        {
            const float distance = lumina_math_sqrt((float) (column * column + row_squared));
            const float intensity = lumina_math_abs(radius - distance);

            if (intensity > 1)
            {
                continue;
            }

            lumina_color_t current_pixel_color = _lumina_style.compositing_color_exterior;

            if (_lumina_style.compositing_mode == LUMINA_STYLE_COMPOSITING_MODE_AUTO)
            {
                current_pixel_color = lumina_get_pixel(x + column, y + row);
            }

            lumina_set_pixel(
                x + column,
                y + row,
                lumina_color_blend(
                    _lumina_style.line_color,
                    current_pixel_color,
                    intensity
                )
            );
        }
    }
}

static inline void lumina_aux_render_circle_quadrants_filled(
    const uint16_t x,
    const uint16_t y,
    const uint16_t radius,
    const int32_t row_start,
    const int32_t row_end,
    const int32_t column_start,
    const int32_t column_end
)
{
    for (int32_t row = row_start; row <= row_end; ++row)
    {
        const int32_t row_squared = row * row;

        for (int32_t column = column_start; column <= column_end; ++column)
        {
            const float distance = lumina_math_sqrt((float) (column * column + row_squared));

            if (distance > radius + 1)
            {
                continue;
            }

            const float intensity = radius - distance + 1;

            if (intensity >= 1)
            {
                lumina_set_pixel(x + column, y + row, _lumina_style.fill_color);
                continue;
            }

            lumina_color_t current_pixel_color = _lumina_style.compositing_color_exterior;

            if (_lumina_style.compositing_mode == LUMINA_STYLE_COMPOSITING_MODE_AUTO)
            {
                current_pixel_color = lumina_get_pixel(x + column, y + row);
            }

            lumina_set_pixel(
                x + column,
                y + row,
                lumina_color_blend(
                    current_pixel_color,
                    _lumina_style.fill_color,
                    intensity
                )
            );
        }
    }
}

void lumina_render_circle_outline(const uint16_t x, const uint16_t y, const uint16_t radius)
{
    lumina_aux_render_circle_quadrants_outline(x, y, radius, -radius, radius, -radius, radius);
}

void lumina_render_circle_filled(const uint16_t x, const uint16_t y, const uint16_t radius)
{
    lumina_aux_render_circle_quadrants_filled(x, y, radius, -radius, radius, -radius, radius);
}

void lumina_render_rectangle_outline(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height)
{
    lumina_render_vertical_line(x, y, height);
    lumina_render_vertical_line(x + width - 1, y, height);
    lumina_render_horizontal_line(x, y, width);
    lumina_render_horizontal_line(x, y + height - 1, width);
}

void lumina_render_rectangle_filled(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height)
{
    for (uint16_t row = y; row < y + height; ++row)
    {
        for (uint16_t column = x; column < x + width; ++column)
        {
            lumina_set_pixel(column, row, _lumina_style.fill_color);
        }
    }
}

void lumina_render_rounded_rectangle_outline(
    const uint16_t x,
    const uint16_t y,
    const uint16_t width,
    const uint16_t height,
    const uint16_t radius
)
{
    const uint16_t double_radius = radius + radius;

    lumina_render_vertical_line(x, y + radius, height - double_radius);
    lumina_render_vertical_line(x + width, y + radius, height - double_radius);
    lumina_render_horizontal_line(x + radius, y, width - double_radius);
    lumina_render_horizontal_line(x + radius, y + height, width - double_radius);

    // Top left
    lumina_aux_render_circle_quadrants_outline(
        x + radius,
        y + radius,
        radius,
        -radius,
        0,
        -radius,
        0
    );

    // Top right
    lumina_aux_render_circle_quadrants_outline(
        x + width - radius,
        y + radius,
        radius,
        -radius,
        0,
        0,
        radius
    );

    // Bottom left
    lumina_aux_render_circle_quadrants_outline(
        x + radius,
        y + height - radius,
        radius,
        0,
        radius,
        -radius,
        0
    );

    // Bottom right
    lumina_aux_render_circle_quadrants_outline(
        x + width - radius,
        y + height - radius,
        radius,
        0,
        radius,
        0,
        radius
    );
}

void lumina_render_rounded_rectangle_filled(
    const uint16_t x,
    const uint16_t y,
    const uint16_t width,
    const uint16_t height,
    const uint16_t radius
)
{
    const uint16_t double_radius = radius + radius;

    // Connect the top left and right circle quadrants
    lumina_render_rectangle_filled(x + radius, y, width - double_radius, radius + 1);

    // Fills in the space between the top and bottom
    lumina_render_rectangle_filled(x, y + radius, width + 1, height - double_radius);

    // Connect the bottom left and right circle quadrants
    lumina_render_rectangle_filled(x + radius, y + height - radius, width - double_radius, radius + 1);

    // Top left
    lumina_aux_render_circle_quadrants_filled(
        x + radius,
        y + radius,
        radius,
        -radius,
        0,
        -radius,
        0
    );

    // Top right
    lumina_aux_render_circle_quadrants_filled(
        x + width - radius,
        y + radius,
        radius,
        -radius,
        0,
        0,
        radius
    );

    // Bottom left
    lumina_aux_render_circle_quadrants_filled(
        x + radius,
        y + height - radius,
        radius,
        0,
        radius,
        -radius,
        0
    );

    // Bottom right
    lumina_aux_render_circle_quadrants_filled(
        x + width - radius,
        y + height - radius,
        radius,
        0,
        radius,
        0,
        radius
    );
}

void lumina_render_character(const uint16_t x, const uint16_t y, const char character)
{
    const lumina_font_t *font = _lumina_style.font;
    const uint8_t glyph_data_index = font->glyph_data_index[character];
    const lumina_font_glyph_data_t glyph_data = font->glyph_data[glyph_data_index];

    uint8_t row_iterator = 0;
    uint8_t column_iterator = 0;
    const uint8_t pixel_bitmask = (1 << font->bpp) - 1;

    for (uint16_t glyph_data_iterator = 0; glyph_data_iterator < glyph_data.length; ++glyph_data_iterator)
    {
        const uint8_t glyph_byte = font->glyph_bitmap[glyph_data.glyph_bitmap_index + glyph_data_iterator];

        for (int8_t i = (8 - font->bpp); i >= 0; i -= font->bpp)
        {
            ++column_iterator;

            if (column_iterator > glyph_data.width)
            {
                break;
            }

            const uint8_t pixel_raw_value = ((glyph_byte >> i) & pixel_bitmask);

            if (pixel_raw_value == 0)
            {
                continue;
            }

            const float blend_factor = (pixel_raw_value + 1) / ((float) pixel_bitmask + 1);

            lumina_set_pixel(
                x + column_iterator,
                y + row_iterator + glyph_data.y_offset,
                lumina_color_blend(_lumina_style.compositing_color_exterior, _lumina_style.line_color, blend_factor)
            );
        }

        if (column_iterator >= glyph_data.width)
        {
            column_iterator = 0;
            ++row_iterator;
        }
    }
}

void lumina_render_text(const uint16_t x, const uint16_t y, const char *text)
{
    if (_lumina_style.font == NULL)
    {
        return;
    }

    uint16_t advance = x;

    for (uint16_t i = 0; i < strlen(text); ++i)
    {
        if (text[i] != ' ')
        {
            lumina_render_character(advance, y, text[i]);
        }

        advance += _lumina_style.font->glyph_data[_lumina_style.font->glyph_data_index[text[i]]].width + 1;
    }
}

void lumina_render_text_aligned(const uint16_t x, const uint16_t y, const char *text, const lumina_text_alignment_t alignment)
{
    if (_lumina_style.font == NULL)
    {
        return;
    }

    // Calculate text width
    uint16_t text_width = 0;

    for (uint16_t i = 0; i < strlen(text); ++i)
    {
        text_width += _lumina_style.font->glyph_data[_lumina_style.font->glyph_data_index[text[i]]].width + 1;
    }

    int16_t x_offset = x;

    switch (alignment)
    {
        case LUMINA_TEXT_ALIGN_LEFT:
            break;

        case LUMINA_TEXT_ALIGN_CENTER:
            x_offset -= text_width / 2;
            break;

        case LUMINA_TEXT_ALIGN_RIGHT:
            x_offset -= text_width;
            break;
    }

    lumina_render_text(x_offset, y, text);
}
