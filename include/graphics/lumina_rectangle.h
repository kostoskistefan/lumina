/**
 * @file:      lumina_rectangle.h
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
#include "lumina_size.h"
#include <stdbool.h>

/**
 * @struct lumina_rectangle_style_t 
 * @brief Describes the style of a rectangle 
 *
 * @var color The color of the rectangle 
 * @var corner_radius The corner radius of the rectangle
 */
typedef struct lumina_rectangle_style_t
{
    bool fill;
    lumina_color_t color;
    uint16_t corner_radius;
} lumina_rectangle_style_t;

/**
 * @brief Render a rectangle
 *
 * @param start_point The starting point of the rectangle 
 * @param size The size of the rectangle
 * @param style The rectangle style
 */
void lumina_graphics_render_rectangle(
    const lumina_point_t start_point,
    const lumina_size_t size,
    const lumina_rectangle_style_t style
);
