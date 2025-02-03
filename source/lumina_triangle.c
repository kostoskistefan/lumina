/**
 * @file:      lumina_triangle.c
 *
 * @date:      29 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_triangle.h"
#include "lumina_math.h"
#include "lumina_driver.h"

lumina_bool_t lumina_triangle_contains_point(
    const lumina_int16_t px,
    const lumina_int16_t py,
    const lumina_uint16_t x0,
    const lumina_uint16_t y0,
    const lumina_uint16_t x1,
    const lumina_uint16_t y1,
    const lumina_uint16_t x2,
    const lumina_uint16_t y2
)
{
    const lumina_int16_t d1 = (px - x0) * (y1 - y0) - (py - y0) * (x1 - x0);
    const lumina_int16_t d2 = (px - x1) * (y2 - y1) - (py - y1) * (x2 - x1);
    const lumina_int16_t d3 = (px - x2) * (y0 - y2) - (py - y2) * (x0 - x2);

    return ((d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0));
}

lumina_float_t lumina_triangle_point_to_line_squared_distance(
    const lumina_int16_t px,
    const lumina_int16_t py,
    const lumina_int16_t x0,
    const lumina_int16_t y0,
    const lumina_int16_t x1,
    const lumina_int16_t y1
)
{
    const lumina_int16_t dx = x1 - x0;
    const lumina_int16_t dy = y1 - y0;
    const lumina_int16_t lx = px - x0;
    const lumina_int16_t ly = py - y0;

    const lumina_int16_t lineLengthSquared = dx * dx + dy * dy;

    if (lineLengthSquared == 0)
    {
        return lx * lx + ly * ly;
    }

    const lumina_int16_t cross = lx * dy - ly * dx;

    return (cross * cross) / ((lumina_float_t) lineLengthSquared);
}

void lumina_triangle_outline_render(
    const lumina_uint16_t x0,
    const lumina_uint16_t y0,
    const lumina_uint16_t x1,
    const lumina_uint16_t y1,
    const lumina_uint16_t x2,
    const lumina_uint16_t y2,
    const lumina_uint16_t thickness,
    const lumina_color_t color,
    const lumina_color_t compositing_color
)
{
    // TODO: Add implementation for lumina_triangle_outline_render after finding a good algorithm

    (void) x0;
    (void) y0;
    (void) x1;
    (void) y1;
    (void) x2;
    (void) y2;
    (void) thickness;
    (void) color;
    (void) compositing_color;
}

void lumina_triangle_filled_render(
    const lumina_uint16_t x0,
    const lumina_uint16_t y0,
    const lumina_uint16_t x1,
    const lumina_uint16_t y1,
    const lumina_uint16_t x2,
    const lumina_uint16_t y2,
    const lumina_color_t color,
    const lumina_color_t compositing_color
)
{
    const lumina_int16_t min_x = lumina_math_min(lumina_math_min(x0, x1), x2);
    const lumina_int16_t max_x = lumina_math_max(lumina_math_max(x0, x1), x2);
    const lumina_int16_t min_y = lumina_math_min(lumina_math_min(y0, y1), y2);
    const lumina_int16_t max_y = lumina_math_max(lumina_math_max(y0, y1), y2);

    // Loop through all pixels in the bounding box
    for (lumina_uint16_t y = min_y; y <= max_y; ++y)
    {
        lumina_bool_t is_x_at_end_of_visible_scanline_pixels = false;

        for (lumina_uint16_t x = min_x; x <= max_x; ++x)
        {
            if (lumina_triangle_contains_point(x, y, x0, y0, x1, y1, x2, y2) == false)
            {
                continue;
            }

            const lumina_float_t d0 = lumina_triangle_point_to_line_squared_distance(x, y, x0, y0, x1, y1);
            const lumina_float_t d1 = lumina_triangle_point_to_line_squared_distance(x, y, x1, y1, x2, y2);
            const lumina_float_t d2 = lumina_triangle_point_to_line_squared_distance(x, y, x2, y2, x0, y0);

            const lumina_float_t alpha = lumina_math_min(lumina_math_min(d0, d1), d2);

            if (alpha <= 0)
            {
                if (is_x_at_end_of_visible_scanline_pixels == true)
                {
                    break;
                }

                continue;
            }

            is_x_at_end_of_visible_scanline_pixels = true;

            lumina_fill_area(x, y, 1, 1, lumina_color_mix(compositing_color, color, alpha));
        }
    }
}
