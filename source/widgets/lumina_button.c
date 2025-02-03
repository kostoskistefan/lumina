/**
 * @file:      lumina_button.c
 *
 * @date:      28 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_button.h"
#include "lumina_text.h"
#include "lumina_rectangle.h"
#include <stddef.h>

void lumina_button_render(const lumina_button_t *const button)
{
    lumina_rectangle_filled_render(
        button->x,
        button->y,
        button->width - 1,
        button->height - 1,
        button->corner_radius,
        button->background_color,
        button->compositing_color
    );

    lumina_text_render(
        button->text,
        button->x + (button->width >> 1),
        button->y + ((button->height - (button->font->ascent + button->font->descent)) >> 1),
        LUMINA_TEXT_ALIGNMENT_CENTER,
        button->font,
        button->text_color,
        button->background_color
    );
}

void lumina_button_event_handler(lumina_button_t *const button, const int x, const int y)
{
    if (x < button->x ||
        y < button->y ||
        x > button->x + button->width - 1 ||
        y > button->y + button->height - 1 ||
        button->click_callback == NULL
    )
    {
        return;
    }

    button->click_callback();
}
