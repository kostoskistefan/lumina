/**
 * @file:      lumina_circle.h
 *
 * @date:      12 July 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#pragma once

#include "lumina_color.h"
#include "lumina_point.h"
#include <stdbool.h>

/**
 * @struct lumina_circle_style_t 
 * @brief Describes the style of a circle 
 *
 * @var color The color of the circle 
 */
typedef struct lumina_circle_style_t
{
    bool fill;
    lumina_color_t color;
} lumina_circle_style_t;

/**
 * @brief Render a circle 
 *
 * @param center_point The center point of the circle 
 * @param radius The radius of the circle 
 * @param style The circle style
 */
void lumina_graphics_render_circle(
    const lumina_point_t center_point,
    const uint16_t radius,
    const lumina_circle_style_t style
);
