/**
 * @file:      lumina_label.h
 *
 * @date:      02 February 2025
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_LABEL_H
#define LUMINA_LABEL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lumina_text.h"
#include "lumina_font.h"
#include "lumina_color.h"
#include "lumina_types.h"

typedef struct lumina_label_t
{
    const lumina_uint16_t x;
    const lumina_uint16_t y;

    const lumina_char_t *text;
    const lumina_font_t *const font;
    const lumina_text_alignment_t text_alignment;

    lumina_color_t text_color;
    lumina_color_t background_color;

    lumina_uint16_t _width;
    lumina_uint16_t _height;
} lumina_label_t;

void lumina_label_render(lumina_label_t *const label);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_LABEL_H
