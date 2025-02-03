/**
 * @file:      lumina_line.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_LINE_H
#define LUMINA_LINE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lumina_types.h"
#include "lumina_color.h"
#include "lumina_driver.h"

void lumina_line_render(
    lumina_uint16_t x0,
    lumina_uint16_t y0,
    lumina_uint16_t x1,
    lumina_uint16_t y1,
    const lumina_uint16_t thickness_start,
    // const lumina_uint16_t thickness_end,
    const lumina_color_t line_color,
    const lumina_color_t compositing_color
);

static inline void lumina_line_vertical_render(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t length,
    const lumina_uint16_t thickness,
    const lumina_color_t color
)
{
    lumina_fill_area(x, y, thickness, length, color);
}

static inline void lumina_line_horizontal_render(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t length,
    const lumina_uint16_t thickness,
    const lumina_color_t color
)
{
    lumina_fill_area(x, y, length, thickness, color);
}

#ifdef __cplusplus
}
#endif

#endif // LUMINA_LINE_H
