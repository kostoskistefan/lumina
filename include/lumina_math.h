/**
 * @file:      lumina_math.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_MATH_H
#define LUMINA_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

#define lumina_math_abs(a)    ((a) < (0) ? -(a) : (a))
#define lumina_math_min(a, b) ((a) < (b) ? (a) : (b))
#define lumina_math_max(a, b) ((a) > (b) ? (a) : (b))
#define lumina_math_clamp(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

#define lumina_math_ceil(x) ceil(x)
#define lumina_math_floor(x) floor(x)

#define lumina_math_lerp(x, x1, y1, x2, y2) ((x1) + ((((x2) - (x1)) / (lumina_float_t) ((y2) - (y1))) * ((x) - (y1))));

#ifdef __cplusplus
}
#endif

#endif // LUMINA_MATH_H
