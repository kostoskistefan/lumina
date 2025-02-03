/**
 * @file:      lumina_toggle_button.c
 *
 * @date:      29 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_toggle_button.h"
#include "lumina_math.h"
#include "lumina_color.h"
#include "lumina_rectangle.h"
#include <stddef.h>

void lumina_toggle_button_render(const lumina_toggle_button_t *const toggle_button)
{
    const lumina_uint16_t min_side = lumina_math_min(toggle_button->width, toggle_button->height);
    const lumina_uint16_t max_side = lumina_math_max(toggle_button->width, toggle_button->height);
    const lumina_uint16_t knob_size = min_side - 5;

    lumina_uint16_t knob_offset = 2;
    lumina_color_t background_color = toggle_button->inactive_color;

    if (toggle_button->state == LUMINA_TOGGLE_BUTTON_STATE_ACTIVE)
    {
        background_color = toggle_button->active_color;
        knob_offset = max_side - knob_size - 3;
    }

    // Render the background
    lumina_rectangle_filled_render(
        toggle_button->x,
        toggle_button->y,
        toggle_button->width - 1,
        toggle_button->height - 1,
        toggle_button->corner_radius,
        background_color,
        toggle_button->compositing_color
    );

    // Render the knob
    if (min_side == toggle_button->height)
    {
        lumina_rectangle_filled_render(
            toggle_button->x + knob_offset,
            toggle_button->y + 2,
            knob_size,
            knob_size,
            toggle_button->corner_radius - 2,
            toggle_button->knob_color,
            background_color
        );
    }

    else
    {
        lumina_rectangle_filled_render(
            toggle_button->x + 2,
            toggle_button->y + knob_offset,
            knob_size,
            knob_size,
            toggle_button->corner_radius - 2,
            toggle_button->knob_color,
            background_color
        );
    }
}

void lumina_toggle_button_event_handler(lumina_toggle_button_t *const toggle_button, const int x, const int y)
{
    if (x < toggle_button->x ||
        y < toggle_button->y ||
        x > toggle_button->x + toggle_button->width - 1 ||
        y > toggle_button->y + toggle_button->height - 1
    )
    {
        return;
    }

    if (toggle_button->click_callback != NULL)
    {
        toggle_button->click_callback(toggle_button->state);
    }

    toggle_button->state = !toggle_button->state;
}
