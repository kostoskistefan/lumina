/**
 * @file:      lumina_toggle_button.h
 *
 * @date:      17 December 2024
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
#include "lumina_types.h"
#include "lumina_color.h"

typedef struct lumina_toggle_button_style_t
{
    lumina_uint8_t corner_radius;

    lumina_color_t knob_color;
    lumina_color_t active_background_color;
    lumina_color_t inactive_background_color;
    lumina_color_t compositing_color;
} lumina_toggle_button_style_t;

typedef struct lumina_toggle_button_t
{
    lumina_uint16_t x;
    lumina_uint16_t y;
    lumina_uint16_t width;
    lumina_uint16_t height;

    lumina_bool_t is_active;

    const lumina_toggle_button_style_t *style;

    void *data;
    void (*on_toggle)(const lumina_bool_t state, void *data);
} lumina_toggle_button_t;

void lumina_toggle_button_initialize(
    lumina_toggle_button_t *const toggle_button,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_uint16_t width,
    const lumina_uint16_t height,
    const lumina_toggle_button_style_t *style,
    void (*on_toggle)(const lumina_bool_t state, void *data),
    void *data
);

void lumina_toggle_button_render(lumina_toggle_button_t *const toggle_button);

void lumina_toggle_button_read(
    lumina_toggle_button_t *const toggle_button,
    const lumina_uint16_t x,
    const lumina_uint16_t y
);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_TOGGLE_BUTTON_H
