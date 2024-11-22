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
extern "C" {
#endif

#include "lumina_types.h"
#include "lumina_color.h"
#include "lumina_driver.h"

static inline void lumina_render_line_vertical(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t length,
    const lumina_color_t color
)
{
    lumina_fill_area(x, y, 1, length, color);
}

static inline void lumina_render_line_horizontal(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t length,
    const lumina_color_t color
)
{
    lumina_fill_area(x, y, length, 1, color);
}

#ifdef __cplusplus
}
#endif

#endif // LUMINA_LINE_H
