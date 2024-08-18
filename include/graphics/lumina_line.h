/**
 * @file:      line.h
 *
 * @date:      12 July 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public
 * License version 3. For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#pragma once

#include "lumina_color.h"
#include "lumina_point.h"

/**
 * @struct lumina_line_style_t 
 * @brief Describes the style of a line
 *
 * @var color The color of the line
 */
typedef struct lumina_line_style_t
{
    lumina_color_t color;
} lumina_line_style_t;

/**
 * @brief Renders a horizontal line
 *
 * @param start_point The starting point of the line
 * @param length The length of the line
 * @param style The style of the line
 */
void lumina_graphics_render_line_horizontal(
    const lumina_point_t start_point,
    const uint16_t length,
    const lumina_line_style_t style
);

/**
 * @brief Renders a vertical line
 *
 * @param start_point The starting point of the line
 * @param length The length of the line
 * @param style The style of the line
 */
void lumina_graphics_render_line_vertical(
    const lumina_point_t start_point,
    const uint16_t length,
    const lumina_line_style_t style
);

/**
 * @brief Render a line between two points
 *
 * @param start_point The starting point of the line
 * @param end_point The ending point of the line
 * @param style The line style
 */
void lumina_graphics_render_line(
    const lumina_point_t start_point,
    const lumina_point_t end_point,
    const lumina_line_style_t style
);
