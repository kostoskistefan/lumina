/**
 * @file:      lumina_color.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_COLOR_H
#define LUMINA_COLOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lumina_types.h"

typedef lumina_uint32_t lumina_color_t;

lumina_color_t lumina_color_mix(
    const lumina_color_t color1,
    const lumina_color_t color2,
    const lumina_float_t amount
);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_COLOR_H
