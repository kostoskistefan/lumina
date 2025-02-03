/**
 * @file:      lumina_spinbox.c
 *
 * @date:      29 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_spinbox.h"
#include "lumina_math.h"
#include "lumina_text.h"
#include "lumina_rectangle.h"
#include <stdio.h>
#include <stddef.h>

static inline void lumina_spinbox_button_render(
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_char_t *text,
    const lumina_font_t *const font,
    const lumina_uint16_t corner_radius,
    const lumina_color_t text_color,
    const lumina_color_t background_color,
    const lumina_color_t compositing_color
)
{
    lumina_rectangle_filled_render(
        x,
        y,
        width - 1,
        height - 1,
        corner_radius,
        background_color,
        compositing_color
    );

    lumina_text_render(
        text,
        x + (width >> 1),
        y + ((height - (font->ascent + font->descent)) >> 1) - 2,
        LUMINA_TEXT_ALIGNMENT_CENTER,
        font,
        text_color,
        background_color
    );
}

void lumina_spinbox_render(const lumina_spinbox_t *const spinbox)
{
    const lumina_uint16_t min_side = lumina_math_min(spinbox->width, spinbox->height);

    lumina_spinbox_button_render(
        spinbox->x,
        spinbox->y,
        min_side,
        min_side,
        "-",
        spinbox->font,
        spinbox->corner_radius,
        spinbox->button_text_color,
        spinbox->button_background_color,
        spinbox->compositing_color
    );

    lumina_spinbox_button_render(
        spinbox->width - min_side + spinbox->x,
        spinbox->y,
        min_side,
        min_side,
        "+",
        spinbox->font,
        spinbox->corner_radius,
        spinbox->button_text_color,
        spinbox->button_background_color,
        spinbox->compositing_color
    );

    lumina_char_t value_buffer[7]; // min value is -32768, which is 7 characters long + null terminator

    snprintf(value_buffer, 7, "%d", spinbox->value);

    lumina_rectangle_filled_render(
        spinbox->x + min_side + 1,
        spinbox->y,
        spinbox->width - min_side * 2 - 3,
        spinbox->height - 1,
        spinbox->corner_radius,
        spinbox->text_background_color,
        spinbox->compositing_color
    );

    lumina_text_render(
        value_buffer,
        spinbox->x + (spinbox->width >> 1),
        spinbox->y + ((spinbox->height - (spinbox->font->ascent + spinbox->font->descent)) >> 1) - 2,
        LUMINA_TEXT_ALIGNMENT_CENTER,
        spinbox->font,
        spinbox->text_color,
        spinbox->text_background_color
    );
}

void lumina_spinbox_event_handler(lumina_spinbox_t *const spinbox, const int x, const int y)
{
    const lumina_uint16_t min_side = lumina_math_min(spinbox->width, spinbox->height);

    if (x >= spinbox->x &&
        y >= spinbox->y &&
        x <= spinbox->x + min_side &&
        y < spinbox->y + min_side &&
        spinbox->decrement_callback != NULL
    )
    {
        spinbox->decrement_callback();
        return;
    }

    if (x >= spinbox->width - min_side + spinbox->x &&
        y >= spinbox->y &&
        x <= spinbox->width + spinbox->x &&
        y < spinbox->y + min_side &&
        spinbox->increment_callback != NULL
    )
    {
        spinbox->increment_callback();
    }
}
