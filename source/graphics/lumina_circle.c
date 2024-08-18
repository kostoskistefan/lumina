/**
 * @file:      lumina_circle.c
 *
 * @date:      12 July 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#include "graphics/lumina_circle.h"
#include "graphics/lumina_line.h"

extern void lumina_pixel_set(const uint16_t x, const uint16_t y, const lumina_color_t color);

static inline void lumina_graphics_render_circle_octants_outline(
    const lumina_point_t center_point,
    const lumina_point_t offsets,
    const lumina_circle_style_t style
)
{
    lumina_pixel_set(center_point.x + offsets.x, center_point.y + offsets.y, style.color);
    lumina_pixel_set(center_point.x - offsets.x, center_point.y + offsets.y, style.color);
    lumina_pixel_set(center_point.x + offsets.x, center_point.y - offsets.y, style.color);
    lumina_pixel_set(center_point.x - offsets.x, center_point.y - offsets.y, style.color);
    lumina_pixel_set(center_point.y + offsets.y, center_point.x + offsets.x, style.color);
    lumina_pixel_set(center_point.y + offsets.y, center_point.x - offsets.x, style.color);
    lumina_pixel_set(center_point.y - offsets.y, center_point.x + offsets.x, style.color);
    lumina_pixel_set(center_point.y - offsets.y, center_point.x - offsets.x, style.color);
}

static inline void lumina_graphics_render_circle_octants_filled(

    const lumina_point_t center_point,
    const lumina_point_t offsets,
    const lumina_line_style_t line_style
)
{
    const uint16_t double_x = 2 * offsets.x;
    const uint16_t double_y = 2 * offsets.y;

    lumina_point_t point;

    point.x = center_point.x - offsets.x;
    point.y = center_point.y - offsets.y;
    lumina_graphics_render_line_horizontal(point, double_x, line_style);

    point.y = center_point.y + offsets.y;
    lumina_graphics_render_line_horizontal(point, double_x, line_style);

    point.x = center_point.y - offsets.y;
    point.y = center_point.x - offsets.x;
    lumina_graphics_render_line_horizontal(point, double_y, line_style);

    point.y = center_point.x + offsets.x;
    lumina_graphics_render_line_horizontal(point, double_y, line_style);
}

void lumina_graphics_render_circle(
    const lumina_point_t center_point,
    const uint16_t radius,
    const lumina_circle_style_t style
)
{
    // TODO: Check for overflow and screen boundary

    int16_t error = -radius;

    uint16_t x = radius;
    uint16_t y = 0;

    if (style.fill == false)
    {
        while (x >= y)
        {
            lumina_graphics_render_circle_octants_outline(center_point, (lumina_point_t) { x, y }, style);

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

        while (x >= y)
        {
            lumina_graphics_render_circle_octants_filled(center_point, (lumina_point_t) { x, y }, line_style);

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
}
