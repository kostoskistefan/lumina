/**
 * @file:      lumina_toggle_button.h
 *
 * @date:      29 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_TOGGLE_BUTTON_H
#define LUMINA_TOGGLE_BUTTON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lumina_font.h"
#include "lumina_color.h"
#include "lumina_types.h"

typedef enum lumina_toggle_button_state_t
{
    LUMINA_TOGGLE_BUTTON_STATE_ACTIVE,
    LUMINA_TOGGLE_BUTTON_STATE_INACTIVE
} lumina_toggle_button_state_t;

typedef struct lumina_toggle_button_t
{
    lumina_toggle_button_state_t state;

    const lumina_uint16_t x;
    const lumina_uint16_t y;
    const lumina_uint16_t width;
    const lumina_uint16_t height;

    const lumina_uint8_t corner_radius;

    lumina_color_t knob_color;
    lumina_color_t active_color;
    lumina_color_t inactive_color;
    lumina_color_t compositing_color;

    void (*click_callback)(const lumina_toggle_button_state_t state);
} lumina_toggle_button_t;

void lumina_toggle_button_render(const lumina_toggle_button_t *const toggle_button);
void lumina_toggle_button_event_handler(lumina_toggle_button_t *const toggle_button, const int x, const int y);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_TOGGLE_BUTTON_H
