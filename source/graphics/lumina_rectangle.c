/**
 * @file:      lumina_rectangle.c
 *
 * @date:      12 July 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#include "graphics/lumina_rectangle.h"
#include "graphics/lumina_line.h"

extern void lumina_pixel_set(const uint16_t x, const uint16_t y, const lumina_color_t color);

void lumina_graphics_render_rectangle(
    const lumina_point_t start_point,
    const lumina_size_t size,
    const lumina_rectangle_style_t style
)
{
    // TODO: Check for overflows and screen boundaries
    // TODO: Check if corner radius is bigger than half the width or height
    const uint16_t double_radius = 2 * style.corner_radius;
    const uint16_t width = size.width - double_radius;
    const uint16_t height = size.height - double_radius;

    // Render outline
    if (style.fill == false)
    {
        const lumina_line_style_t line_style = (lumina_line_style_t) { .color = style.color };

        lumina_point_t point;

        // Render the horizontal lines of the rectangle
        // Top
        point.x = start_point.x + style.corner_radius;
        point.y = start_point.y;
        lumina_graphics_render_line_horizontal(point, width, line_style);

        // Bottom
        point.y = start_point.y + size.height;
        lumina_graphics_render_line_horizontal(point, width, line_style);

        // Render the vertical lines of the rectangle
        // Left
        point.x = start_point.x;
        point.y = start_point.y + style.corner_radius;
        lumina_graphics_render_line_vertical(point, height, line_style);

        // Right
        point.x = start_point.x + size.width;
        lumina_graphics_render_line_vertical(point, height, line_style);

        // If the corner radius is 0, there nothing else to be done
        if (style.corner_radius == 0)
        {
            return;
        }
    }

    // Render filled rectangle without rounded corners
    else
    {
        if (style.corner_radius == 0)
        {
            const lumina_line_style_t line_style = (lumina_line_style_t) { .color = style.color };
            lumina_point_t point = { .x = start_point.x, .y = start_point.y };

            for (uint16_t y = start_point.y; y < start_point.y + size.height; ++y)
            {
                point.y = y;

                lumina_graphics_render_line_horizontal(
                    point,
                    size.width,
                    line_style
                );
            }

            return;
        }
    }

    // Render corners
    int16_t error = -style.corner_radius;

    uint16_t x = style.corner_radius;
    uint16_t y = 0;

    const uint16_t start_x_plus_radius = start_point.x + style.corner_radius;
    const uint16_t start_y_plus_radius = start_point.y + style.corner_radius;
    const uint16_t start_x_width_offset = start_point.x + size.width - style.corner_radius;
    const uint16_t start_y_width_offset = start_point.y + size.width - style.corner_radius;
    const uint16_t start_x_height_offset = start_point.x + size.height - style.corner_radius;
    const uint16_t start_y_height_offset = start_point.y + size.height - style.corner_radius;

    if (style.fill == false)
    {
        while (x >= y)
        {
            // Top left
            lumina_pixel_set(start_x_plus_radius - x, start_y_plus_radius - y, style.color);
            lumina_pixel_set(start_y_plus_radius - y, start_x_plus_radius - x, style.color);

            // Top right
            lumina_pixel_set(start_x_width_offset + x, start_y_plus_radius - y, style.color);
            lumina_pixel_set(start_y_width_offset + y, start_x_plus_radius - x, style.color);

            // Bottom left
            lumina_pixel_set(start_x_plus_radius - x, start_y_height_offset + y, style.color);
            lumina_pixel_set(start_y_plus_radius - y, start_x_height_offset + x, style.color);

            // Bottom right
            lumina_pixel_set(start_x_width_offset + x, start_y_height_offset + y, style.color);
            lumina_pixel_set(start_y_width_offset + y, start_x_height_offset + x, style.color);

            error += y;
            ++y;
            error += y;

            if (error >= 0)
            {
                --x;
                error -= x;
                error -= x;
            }
        }
    }

    else
    {
        const lumina_line_style_t line_style = (lumina_line_style_t) { .color = style.color };

        // Render rounded corners
        while (x >= y)
        {
            const uint16_t double_x = 2 * x;
            const uint16_t double_y = 2 * y;

            lumina_point_t point;

            point.x = start_point.x + style.corner_radius - x;
            point.y = start_point.y + style.corner_radius - y;
            lumina_graphics_render_line_horizontal(point, width + 1 + double_x, line_style);

            point.y = start_point.y + size.height - style.corner_radius + y;
            lumina_graphics_render_line_horizontal(point, width + 1 + double_x, line_style);

            point.x = start_point.y + style.corner_radius - y;
            point.y = start_point.x + style.corner_radius - x;
            lumina_graphics_render_line_horizontal(point, width + 1 + double_y, line_style);

            point.y = start_point.x + size.height - style.corner_radius + x;
            lumina_graphics_render_line_horizontal(point, width + 1 + double_y, line_style);

            error += y;
            ++y;
            error += y;

            if (error >= 0)
            {
                --x;
                error -= x;
                error -= x;
            }
        }

        // Fill center
        lumina_point_t point = { .x = start_point.x, .y = start_point.y + style.corner_radius };

        for (uint16_t y = start_point.y + style.corner_radius; y < start_point.y + size.height - style.corner_radius; ++y)
        {
            point.y = y;
            lumina_graphics_render_line_horizontal(point, size.width + 1, line_style);
        }
    }
}
