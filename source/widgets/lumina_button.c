/**
 * @file:      lumina_button.c
 *
 * @date:      16 December 2024
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

void lumina_button_initialize(
    lumina_button_t *const button,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_char_t *text,
    const lumina_button_style_t *style,
    void (*on_click)(void *data),
    void *data
)
{
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    button->text = text;
    button->style = style;
    button->on_click = on_click;
    button->data = data;
}

void lumina_button_read(const lumina_button_t *const button, const lumina_uint16_t x, const lumina_uint16_t y)
{
    if (button->on_click == NULL)
    {
        return;
    }

    if (x >= button->x && x <= button->x + button->width && y >= button->y && y <= button->y + button->height)
    {
        button->on_click(button->data);
    }
}

void lumina_button_render(lumina_button_t *const button)
{
    if (button->style == NULL)
    {
        return;
    }

    lumina_render_rectangle_filled(
        button->x,
        button->y,
        button->width,
        button->height,
        button->style->corner_radius,
        button->style->background_color,
        button->style->compositing_color
    );

    if (button->text == NULL)
    {
        return;
    }

    lumina_render_text(
        button->text,
        button->x + (button->width >> 1),
        button->y + ((button->height - (button->style->font->ascent + button->style->font->descent)) >> 1),
        button->style->text_alignment,
        (lumina_text_style_t *) button->style
    );
}
