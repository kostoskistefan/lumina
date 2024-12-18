/**
* @file:      lumina_label.h
*
* @date:      17 December 2024
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

typedef struct lumina_label_style_t
{
    const lumina_text_style_t *text_style;
    lumina_text_alignment_t text_alignment;
} lumina_label_style_t;

typedef struct lumina_label_t
{
    const lumina_char_t *text;
    const lumina_label_style_t *style;

    lumina_uint16_t _x;
    lumina_uint16_t _y;

    lumina_uint16_t _text_width;
    lumina_uint16_t _x_alignment_offset;
} lumina_label_t;

void lumina_label_initialize(lumina_label_t *const label, const lumina_label_style_t *style);
void lumina_label_set_text(lumina_label_t *const label, const lumina_char_t *text);
void lumina_label_render(lumina_label_t *const label, const lumina_uint16_t x, const lumina_uint16_t y);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_LABEL_H
