/**
 * @file:      lumina_color.c
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_color.h"

lumina_color_t lumina_color_mix(const lumina_color_t color1, const lumina_color_t color2, const lumina_float_t amount)
{
    if (amount <= 0.0f)
    {
        return color1;
    }

    if (amount >= 1.0f)
    {
        return color2;
    }

    const uint8_t red1 = (color1 >> 16) & 0xff;
    const uint8_t green1 = (color1 >> 8) & 0xff;
    const uint8_t blue1 = color1 & 0xff;

    const uint8_t red2 = (color2 >> 16) & 0xff;
    const uint8_t green2 = (color2 >> 8) & 0xff;
    const uint8_t blue2 = color2 & 0xff;

    const uint8_t red_blend = red1 + (red2 - red1) * amount;
    const uint8_t green_blend = green1 + (green2 - green1) * amount;
    const uint8_t blue_blend = blue1 + (blue2 - blue1) * amount;

    return (red_blend << 16) | (green_blend << 8) | blue_blend;
}
