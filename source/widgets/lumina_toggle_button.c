/**
 * @file:      lumina_toggle_button.c
 *
 * @date:      17 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_toggle_button.h"
#include "lumina_rectangle.h"
#include "lumina_math.h"

void lumina_toggle_button_initialize(
    lumina_toggle_button_t *const toggle_button,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_toggle_button_style_t *style,
    void (*on_toggle)(const lumina_bool_t state, void *data),
    void *data
)
{
    toggle_button->x = x;
    toggle_button->y = y;
    toggle_button->width = width;
    toggle_button->height = height;
    toggle_button->style = style;
    toggle_button->is_active = false;
    toggle_button->on_toggle = on_toggle;
    toggle_button->data = data;
}

void lumina_toggle_button_read(
    lumina_toggle_button_t *const toggle_button,
    const lumina_uint16_t x,
    const lumina_uint16_t y
)
{
    if (x >= toggle_button->x &&
        y >= toggle_button->y &&
        x <= toggle_button->x + toggle_button->width &&
        y <= toggle_button->y + toggle_button->height)
    {
        toggle_button->is_active = !toggle_button->is_active;

        if (toggle_button->on_toggle != NULL)
        {
            toggle_button->on_toggle(toggle_button->is_active, toggle_button->data);
        }
    }
}

void lumina_toggle_button_render(lumina_toggle_button_t *const toggle_button)
{
    if (toggle_button->style == NULL)
    {
        return;
    }

    lumina_color_t background_color = toggle_button->style->inactive_background_color;

    if (toggle_button->is_active == true)
    {
        background_color = toggle_button->style->active_background_color;
    }

    lumina_render_rectangle_filled(
        toggle_button->x,
        toggle_button->y,
        toggle_button->width,
        toggle_button->height,
        toggle_button->style->corner_radius,
        background_color,
        toggle_button->style->compositing_color
    );

    const lumina_uint16_t knob_size = toggle_button->height - 4;
    const lumina_uint16_t corner_radius = lumina_math_max(0, toggle_button->style->corner_radius - 2);

    lumina_uint16_t knob_x = toggle_button->x + 2;

    if (toggle_button->is_active == true)
    {
        knob_x = toggle_button->x + toggle_button->width - knob_size - 2;
    }

    lumina_render_rectangle_filled(
        knob_x,
        toggle_button->y + 2,
        knob_size,
        knob_size,
        corner_radius,
        toggle_button->style->knob_color,
        background_color
    );
}
