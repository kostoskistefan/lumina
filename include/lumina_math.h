/**
 * @file:      lumina_math.h
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

#include <math.h>

#define lumina_math_abs(x) ((x) < 0 ? -(x) : (x))
#define lumina_math_max(x, y) ((x) > (y) ? (x) : (y))
#define lumina_math_min(x, y) ((x) < (y) ? (x) : (y))
#define lumina_math_clamp(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define lumina_math_sqrt(x) sqrt(x)
#define lumina_math_ceil(x) ceil(x)
#define lumina_math_floor(x) floor(x)
#define lumina_math_round(x) round(x)
