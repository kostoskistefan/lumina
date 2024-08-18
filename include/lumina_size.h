/**
 * @file:      lumina_size.h
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
 * @typedef lumina_size_t
 * @brief Represents a size in 2D space
 *
 * @var width The width
 * @var height The height
 */
typedef struct lumina_size_t
{
    uint16_t width;
    uint16_t height;
} lumina_size_t;
