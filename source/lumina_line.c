/**
 * @file:      lumina_line.c
 *
 * @date:      20 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_line.h"
#include "lumina_math.h"

void lumina_line_render(
    lumina_uint16_t x0,
    lumina_uint16_t y0,
    lumina_uint16_t x1,
    lumina_uint16_t y1,
    const lumina_uint16_t thickness,
    const lumina_color_t line_color,
    const lumina_color_t compositing_color
)
{
    if (thickness == 0)
    {
        return;
    }

    if (x0 > x1)
    {
        lumina_math_swap(x0, x1, lumina_uint16_t);
    }

    if (y0 > y1)
    {
        lumina_math_swap(y0, y1, lumina_uint16_t);
    }

    const lumina_uint16_t dx = x1 - x0;
    const lumina_uint16_t dy = y1 - y0;
    const lumina_bool_t is_steep = dy > dx;

    const lumina_color_t endpoint_color = lumina_color_mix(compositing_color, line_color, 0.5f);

    if (is_steep == true)
    {
        const lumina_float_t slope = dx / (lumina_float_t) dy;

        // Draw end points
        lumina_fill_area(x0, y0, thickness, 1, endpoint_color);
        lumina_fill_area(x1, y1, thickness, 1, endpoint_color);

        // Draw main line
        lumina_float_t x_step = x0 + slope;

        for (lumina_uint16_t y = y0 + 1; y < y1; ++y)
        {
            const lumina_uint16_t x = (lumina_uint16_t) x_step;
            const lumina_float_t alpha = x_step - x;

            lumina_fill_area(x, y, 1, 1, lumina_color_mix(compositing_color, line_color, 1 - alpha));
            lumina_fill_area(x + 1, y, thickness - 1, 1, line_color);
            lumina_fill_area(x + thickness, y, 1, 1, lumina_color_mix(compositing_color, line_color, alpha));

            x_step += slope;
        }
    }

    else
    {
        const lumina_float_t slope = dy / (lumina_float_t) dx;

        // Draw end points
        lumina_fill_area(x0, y0, 1, thickness, endpoint_color);
        lumina_fill_area(x1, y1, 1, thickness, endpoint_color);

        // Draw main line
        lumina_float_t y_step = y0 + slope;

        for (lumina_uint16_t x = x0 + 1; x < x1; ++x)
        {
            const lumina_uint16_t y = (lumina_uint16_t) y_step;
            const lumina_float_t alpha = y_step - y;

            lumina_fill_area(x, y, 1, 1, lumina_color_mix(compositing_color, line_color, 1 - alpha));
            lumina_fill_area(x, y + 1, 1, thickness - 1, line_color);
            lumina_fill_area(x, y + thickness, 1, 1, lumina_color_mix(compositing_color, line_color, alpha));

            y_step += slope;
        }
    }
}
