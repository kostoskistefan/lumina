/**
 * @file:      lumina_spinbox.h
 *
 * @date:      29 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_SPINBOX_H
#define LUMINA_SPINBOX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lumina_font.h"
#include "lumina_color.h"
#include "lumina_types.h"

typedef struct lumina_spinbox_t
{
    const lumina_uint16_t x;
    const lumina_uint16_t y;
    const lumina_uint16_t width;
    const lumina_uint16_t height;

    int16_t value;

    const lumina_font_t *font;

    const lumina_uint8_t corner_radius;

    lumina_color_t text_color;
    lumina_color_t text_background_color;
    lumina_color_t button_text_color;
    lumina_color_t button_background_color;
    lumina_color_t compositing_color;

    void (*decrement_callback)(void);
    void (*increment_callback)(void);
} lumina_spinbox_t;

void lumina_spinbox_render(const lumina_spinbox_t *const spinbox);
void lumina_spinbox_event_handler(lumina_spinbox_t *const spinbox, const int x, const int y);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_SPINBOX_H
