/**
 * @file:      lumina_button.h
 *
 * @date:      16 December 2024
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

#include "lumina_text.h"
#include "lumina_font.h"
#include "lumina_types.h"
#include "lumina_color.h"

typedef struct lumina_button_style_t 
{
    // Ordering matters here. First 3 should be the same as text_style
    const lumina_font_t *const font;
    const lumina_color_t text_color;
    const lumina_color_t background_color;

    lumina_uint8_t corner_radius;
    lumina_color_t compositing_color;

    lumina_text_alignment_t text_alignment;
} lumina_button_style_t;

typedef struct lumina_button_t
{
    lumina_uint16_t x;
    lumina_uint16_t y;
    lumina_uint16_t width;
    lumina_uint16_t height;

    const lumina_char_t *text;

    const lumina_button_style_t *style;

    void *data;
    void (*on_click)(void *data);
} lumina_button_t;

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
);

void lumina_button_render(lumina_button_t *const button);

void lumina_button_read(const lumina_button_t *const button, const lumina_uint16_t x, const lumina_uint16_t y);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_BUTTON_H
