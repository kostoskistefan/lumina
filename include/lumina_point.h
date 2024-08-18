/**
 * @file:      lumina_point.h
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
 * @typedef lumina_point_t
 * @brief Represents a point in 2D space
 *
 * @var x The x coordinate of the point
 * @var y The y coordinate of the point
 */
typedef struct lumina_point_t
{
    uint16_t x;
    uint16_t y;
} lumina_point_t;
