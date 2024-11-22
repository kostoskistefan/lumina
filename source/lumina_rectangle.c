/**
 * @file:      lumina_rectangle.c
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_rectangle.h"
#include "lumina_driver.h"

// --------------------------------------------------------------------------------------------------------------------- 
// The code in this file is heavily based on the TFT_eSPI library by Bodmer: https://github.com/Bodmer/TFT_eSPI
// --------------------------------------------------------------------------------------------------------------------- 

static inline lumina_uint8_t sqrt_fraction(lumina_uint16_t number)
{
    lumina_uint16_t bsh = 0x00004000;
    lumina_uint16_t fpr = 0;
    lumina_uint16_t osh = 0;

    while (number > bsh)
    {
        bsh <<= 2;
        osh++;
    }

    do
    {
        const lumina_uint16_t bod = bsh + fpr;

        if (number >= bod)
        {
            number -= bod;
            fpr = bsh + bod;
        }

        number <<= 1;
    } while (bsh >>= 1);

    return fpr >> osh;
}

void lumina_render_rectangle_outline(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_uint16_t outer_corner_radius,
    const lumina_uint16_t inner_corner_radius,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    if (outer_corner_radius == 0)
    {
        lumina_fill_area(x, y, width + 1, 1, foreground_color);
        lumina_fill_area(x, y + height, width + 1, 1, foreground_color);
        lumina_fill_area(x, y + 1, 1, height - 1, foreground_color);
        lumina_fill_area(x + width, y + 1, 1, height - 1, foreground_color);
        return;
    }

    const lumina_uint16_t double_outer_corner_radius = outer_corner_radius + outer_corner_radius;
    const lumina_uint16_t double_inner_corner_radius = inner_corner_radius + inner_corner_radius;

    const lumina_uint16_t width_radius_offset = width - double_outer_corner_radius;
    const lumina_uint16_t height_radius_offset = height - double_outer_corner_radius;

    const lumina_uint16_t inner_radius_squared = inner_corner_radius * inner_corner_radius;
    const lumina_uint16_t outer_radius_squared = outer_corner_radius * outer_corner_radius;
    const lumina_uint16_t outer_antialiasing_zone_radius = outer_radius_squared - double_outer_corner_radius + 1;
    const lumina_uint16_t inner_antialiasing_zone_radius = inner_radius_squared - double_inner_corner_radius + 1;

    lumina_uint16_t top_y = 0;
    lumina_uint16_t left_x = 0;
    lumina_uint16_t right_x = 0;
    lumina_uint16_t bottom_y = 0;

    for (lumina_uint16_t cy = 0; cy < outer_corner_radius; ++cy)
    {
        const lumina_uint16_t dy = outer_corner_radius - cy;
        const lumina_uint16_t dy_squared = dy * dy;

        lumina_uint16_t x_start = 0;

        // Find and track arc zone start point
        while (x_start * (x_start - double_outer_corner_radius) + dy_squared >= 0)
        {
            ++x_start;
        }

        lumina_uint16_t horizontal_line_length = 0;
        lumina_uint16_t right_side_x_start = 0;

        for (lumina_uint16_t cx = x_start; cx < outer_corner_radius; ++cx)
        {
            lumina_uint8_t alpha = 0;

            const lumina_uint16_t dx = outer_corner_radius - cx;
            const lumina_uint16_t dx_squared = dx * dx;
            const lumina_uint16_t hypotenuse_squared = dx_squared + dy_squared;

            // Outer AA zone
            if (hypotenuse_squared > outer_antialiasing_zone_radius)
            {
                alpha = ~sqrt_fraction(hypotenuse_squared);
            }

            else if (hypotenuse_squared >= inner_radius_squared)
            {
                right_side_x_start = cx;
                ++horizontal_line_length;
                continue;
            }

            else
            {
                // Skip inner pixels
                if (hypotenuse_squared <= inner_antialiasing_zone_radius)
                {
                    break;
                }

                // Inner AA zone
                alpha = sqrt_fraction(hypotenuse_squared);
            }

            // Skip low alpha pixels
            if (alpha < 16)
            {
                continue;
            }

            left_x = x + cx;
            top_y = y + cy;
            right_x = x + width - cx;
            bottom_y = y + height - cy;

            const lumina_color_t blended_color = lumina_color_mix(background_color, foreground_color, alpha / 255.0f);

            lumina_fill_area(left_x, top_y, 1, 1, blended_color);
            lumina_fill_area(right_x, top_y, 1, 1, blended_color);
            lumina_fill_area(left_x, bottom_y, 1, 1, blended_color);
            lumina_fill_area(right_x, bottom_y, 1, 1, blended_color);
        }

        left_x = x + right_side_x_start - horizontal_line_length + 1;
        top_y = y + cy;
        right_x = x - right_side_x_start + width;
        bottom_y = y - cy + height;

        lumina_fill_area(left_x, top_y, horizontal_line_length, 1, foreground_color);
        lumina_fill_area(right_x, top_y, horizontal_line_length, 1, foreground_color);
        lumina_fill_area(left_x, bottom_y, horizontal_line_length, 1, foreground_color);
        lumina_fill_area(right_x, bottom_y, horizontal_line_length, 1, foreground_color);
    }

    const lumina_uint16_t radius_difference = outer_corner_radius - inner_corner_radius;

    left_x = x + outer_corner_radius;
    top_y = y + outer_corner_radius;
    right_x = x - radius_difference + width;
    bottom_y = y - radius_difference + height;

    lumina_fill_area(left_x, y + 1, width_radius_offset + 1, radius_difference, foreground_color);    // Top
    lumina_fill_area(x + 1, top_y, radius_difference, height_radius_offset + 1, foreground_color);    // Left
    lumina_fill_area(right_x, top_y, radius_difference, height_radius_offset + 1, foreground_color);  // Right
    lumina_fill_area(left_x, bottom_y, width_radius_offset + 1, radius_difference, foreground_color); // Bottom
}

void lumina_render_rectangle_filled(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_uint16_t corner_radius,
    const lumina_color_t foreground_color,
    const lumina_color_t background_color
)
{
    if (corner_radius == 0)
    {
        lumina_fill_area(x, y, width + 1, height + 1, foreground_color);
        return;
    }

    const lumina_uint16_t double_corner_radius = corner_radius + corner_radius;
    const lumina_uint16_t inner_corner_radius_squared = corner_radius * corner_radius;
    const lumina_uint16_t outer_corner_radius_squared = inner_corner_radius_squared + double_corner_radius - 1;

    lumina_fill_area(x, y + corner_radius, width + 1, height - double_corner_radius + 1, foreground_color);

    for (lumina_uint16_t cy = 0; cy < corner_radius; ++cy)
    {
        lumina_uint16_t top_y = 0;
        lumina_uint16_t left_x = 0;
        lumina_uint16_t right_x = 0;
        lumina_uint16_t bottom_y = 0;

        const lumina_uint16_t dy = corner_radius - cy;
        const lumina_uint16_t dy_squared = dy * dy;

        lumina_uint16_t cx;

        for (cx = 0; cx <= corner_radius; ++cx)
        {
            const lumina_uint16_t dx = corner_radius - cx;
            const lumina_uint16_t dx_squared = dx * dx;
            const lumina_uint16_t hypotenuse_squared = dx_squared + dy_squared;

            if (hypotenuse_squared <= inner_corner_radius_squared)
            {
                break;
            }

            if (hypotenuse_squared >= outer_corner_radius_squared)
            {
                continue;
            }

            const lumina_uint8_t alpha = ~sqrt_fraction(hypotenuse_squared);

            if (alpha > 246)
            {
                break;
            }

            if (alpha < 9)
            {
                continue;
            }

            const lumina_color_t blended_color = lumina_color_mix(background_color, foreground_color, alpha / 255.0f);

            left_x = x + cx;
            top_y = y + cy;
            right_x = x + width - cx;
            bottom_y = y + height - cy;

            lumina_fill_area(left_x, top_y, 1, 1, blended_color);
            lumina_fill_area(right_x, top_y, 1, 1, blended_color);
            lumina_fill_area(left_x, bottom_y, 1, 1, blended_color);
            lumina_fill_area(right_x, bottom_y, 1, 1, blended_color);
        }

        const lumina_uint16_t line_width = width - cx - cx + 1;

        left_x = x + cx;

        lumina_fill_area(left_x, y + cy, line_width, 1, foreground_color);
        lumina_fill_area(left_x, y - cy + height, line_width, 1, foreground_color);
    }
}
