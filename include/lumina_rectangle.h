/**
 * @file:      lumina_rectangle.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_RECTANGLE_H
#define LUMINA_RECTANGLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lumina_types.h"
#include "lumina_color.h"

void lumina_render_rectangle_outline(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_uint16_t outer_corner_radius,
    const lumina_uint16_t inner_corner_radius,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
);

void lumina_render_rectangle_filled(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_uint16_t corner_radius,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_RECTANGLE_H
