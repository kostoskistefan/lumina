/**
 * @file:      lumina_circle.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_CIRCLE_H
#define LUMINA_CIRCLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lumina_types.h"
#include "lumina_color.h"
#include "lumina_rectangle.h"

static inline void lumina_render_circle_outline(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t outer_radius,
    const lumina_uint16_t inner_radius,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    lumina_render_rectangle_outline(
        x - outer_radius,
        y - outer_radius,
        outer_radius + outer_radius,
        outer_radius + outer_radius,
        outer_radius,
        inner_radius,
        foreground_color,
        background_color
    );
}

static inline void lumina_render_circle_filled(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t radius,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    lumina_render_rectangle_filled(
        x - radius,
        y - radius,
        radius + radius,
        radius + radius,
        radius,
        foreground_color,
        background_color
    );
}

#ifdef __cplusplus
}
#endif

#endif // LUMINA_CIRCLE_H
