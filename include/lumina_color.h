/**
 * @file:      lumina_color.h
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

#include <stdint.h>

/**
 * @typedef lumina_color_t
 * @brief Represents a color in RGB format
 */
typedef uint32_t lumina_color_t;

/**
 * @brief Interpolates between two colors
 *
 * @param color_a First color
 * @param color_b Second color
 * @param amount Amount to interpolate
 * @return Interpolated color
 */
lumina_color_t lumina_color_interpolate(
    const lumina_color_t color_a,
    const lumina_color_t color_b,
    const float amount
);
