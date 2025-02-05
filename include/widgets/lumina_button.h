/**
 * @file:      lumina_button.h
 *
 * @date:      29 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_BUTTON_H
#define LUMINA_BUTTON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lumina_font.h"
#include "lumina_color.h"
#include "lumina_types.h"

typedef struct lumina_button_t
{
    const lumina_uint16_t x;
    const lumina_uint16_t y;
    const lumina_uint16_t width;
    const lumina_uint16_t height;

    const lumina_char_t *text;
    const lumina_font_t *font;

    const lumina_uint8_t corner_radius;

    lumina_color_t text_color;
    lumina_color_t background_color;
    lumina_color_t compositing_color;

    void (*click_callback)(void);
} lumina_button_t;

void lumina_button_render(const lumina_button_t *const button);
void lumina_button_event_handler(lumina_button_t *const button, const int x, const int y);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_BUTTON_H
