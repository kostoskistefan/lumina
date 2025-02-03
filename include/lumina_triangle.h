/**
 * @file:      lumina_triangle.h
 *
 * @date:      29 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_TRIANGLE_H
#define LUMINA_TRIANGLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lumina_types.h"
#include "lumina_color.h"

void lumina_triangle_filled_render(
    const lumina_uint16_t x0,
    const lumina_uint16_t y0,
    const lumina_uint16_t x1,
    const lumina_uint16_t y1,
    const lumina_uint16_t x2,
    const lumina_uint16_t y2,
    const lumina_color_t color,
    const lumina_color_t compositing_color
);

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
);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_TRIANGLE_H
