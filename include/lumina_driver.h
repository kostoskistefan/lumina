/**
 * @file:      lumina_driver.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_DRIVER_H
#define LUMINA_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lumina_types.h"
#include "lumina_color.h"

extern void lumina_fill_area(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_color_t color
);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_DRIVER_H
