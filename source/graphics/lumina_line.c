/**
 * @file:      line.c
 *
 * @date:      12 July 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#include "graphics/lumina_line.h"
#include "lumina_math.h"
#include <stdbool.h>

extern void lumina_pixel_set(const uint16_t x, const uint16_t y, const lumina_color_t color);

void lumina_graphics_render_line_horizontal(
    const lumina_point_t start_point,
    const uint16_t length,
    const lumina_line_style_t style
)
{
    // TODO: Check for overflow and screen boundary

    for (uint16_t i = start_point.x; i < start_point.x + length; ++i)
    {
        lumina_pixel_set(i, start_point.y, style.color);
    }
}

/**
 * @brief Renders a vertical line
 *
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param length The length of the line
 * @param style The style of the line
 */
void lumina_graphics_render_line_vertical(
    const lumina_point_t start_point,
    const uint16_t length,
    const lumina_line_style_t style
)
{
    // TODO: Check for overflow and screen boundary

    for (uint16_t i = start_point.y; i < start_point.y + length; ++i)
    {
        lumina_pixel_set(start_point.x, i, style.color);
    }
}

void lumina_graphics_render_line(
    const lumina_point_t start_point,
    const lumina_point_t end_point,
    const lumina_line_style_t style
)
{
    // TODO: Check for overflow and screen boundary

    const int16_t delta_x = lumina_math_abs(end_point.x - start_point.x);
    const int16_t delta_y = lumina_math_abs(end_point.y - start_point.y);

    // Determines the direction of the line
    const int8_t step_x = start_point.x < end_point.x ? 1 : -1;
    const int8_t step_y = start_point.y < end_point.y ? 1 : -1;

    int16_t error = delta_x - delta_y;
    int16_t double_error;

    uint16_t x = start_point.x;
    uint16_t y = start_point.y;

    while (true)
    {
        lumina_pixel_set(x, y, style.color);

        if (x == end_point.x && y == end_point.y)
        {
            break;
        }

        double_error = 2 * error;

        // Iterate over the X axis
        if (double_error >= -delta_y)
        {
            x += step_x;
            error -= delta_y;
        }

        // Iterate over the Y axis
        if (double_error <= delta_x)
        {
            y += step_y;
            error += delta_x;
        }
    }
}
