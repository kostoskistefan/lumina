/**
 * @file:      lumina_text.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_TEXT_H
#define LUMINA_TEXT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lumina_font.h"
#include "lumina_color.h"
#include "lumina_types.h"

typedef enum lumina_text_alignment_t
{
    LUMINA_TEXT_ALIGNMENT_LEFT,
    LUMINA_TEXT_ALIGNMENT_CENTER,
    LUMINA_TEXT_ALIGNMENT_RIGHT,
} lumina_text_alignment_t;

typedef struct lumina_text_style_t
{
    const lumina_font_t *const font;
    const lumina_color_t foreground_color;
    const lumina_color_t background_color;
} lumina_text_style_t;

void lumina_render_text(
    const lumina_char_t *text,
    const lumina_uint16_t x,
    const lumina_uint16_t y,
    const lumina_text_alignment_t alignment,
    const lumina_text_style_t *const style
);

lumina_uint16_t lumina_text_get_width(const lumina_char_t *text, const lumina_font_t *const font);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_TEXT_H
