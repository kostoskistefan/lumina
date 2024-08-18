/**
 * @file:      lumina_color.c
 *
 * @date:      17 August 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#include "lumina_color.h"

lumina_color_t lumina_color_interpolate(
    const lumina_color_t color1,
    const lumina_color_t color2,
    const float amount
)
{
    if (amount <= 0.0f)
    {
        return color1;
    }

    else if (amount >= 1.0f)
    {
        return color2;
    }

    // Split the colors into their RGB components
    const uint8_t red1 = (color1 >> 16) & 0xff;
    const uint8_t green1 = (color1 >> 8) & 0xff;
    const uint8_t blue1 = color1 & 0xff;

    const uint8_t red2 = (color2 >> 16) & 0xff;
    const uint8_t green2 = (color2 >> 8) & 0xff;
    const uint8_t blue2 = color2 & 0xff;

    // Interpolate the RGB components
    const uint8_t red = red1 + (red2 - red1) * amount;
    const uint8_t green = green1 + (green2 - green1) * amount;
    const uint8_t blue = blue1 + (blue2 - blue1) * amount;

    // Combine the RGB components
    return (red << 16) | (green << 8) | blue;
}
