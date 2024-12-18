/**
 * @file:      lumina_label.c
 *
 * @date:      17 December 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_label.h"
#include "lumina_text.h"
#include "lumina_rectangle.h"
#include <stdio.h>

static void lumina_label_calculate_x_alignment_offset(lumina_label_t *const label);
static void lumina_label_render_background(const lumina_label_t *const label);

void lumina_label_initialize(
    lumina_label_t *const label,
    const lumina_label_style_t *style
)
{
    label->_x = 0;
    label->_y = 0;
    label->text = NULL;
    label->style = style;
    label->_text_width = 0;
    label->_x_alignment_offset = 0;
}

void lumina_label_set_text(lumina_label_t *const label, const lumina_char_t *text)
{
    lumina_label_render_background(label);

    label->text = text;

    lumina_label_calculate_x_alignment_offset(label);
}

void lumina_label_render(lumina_label_t *const label, const lumina_uint16_t x, const lumina_uint16_t y)
{
    if (label->text == NULL)
    {
        return;
    }

    label->_x = x;
    label->_y = y;

    lumina_label_render_background(label);

    lumina_render_text(
        label->text,
        label->_x,
        label->_y,
        label->style->text_alignment,
        label->style->text_style
    );
}

static void lumina_label_calculate_x_alignment_offset(lumina_label_t *const label)
{
    label->_text_width = lumina_text_get_width(label->text, label->style->text_style->font);

    switch (label->style->text_alignment)
    {
        case LUMINA_TEXT_ALIGNMENT_LEFT:
            label->_x_alignment_offset = 0;
            break;

        case LUMINA_TEXT_ALIGNMENT_CENTER:
            label->_x_alignment_offset = (label->_text_width >> 1);
            break;

        case LUMINA_TEXT_ALIGNMENT_RIGHT:
            label->_x_alignment_offset = label->_text_width;
            break;
    }
}

static void lumina_label_render_background(const lumina_label_t *const label)
{
    lumina_render_rectangle_filled(
        label->_x - label->_x_alignment_offset,
        label->_y,
        label->_text_width,
        label->style->text_style->font->ascent + label->style->text_style->font->descent,
        0,
        label->style->text_style->background_color,
        label->style->text_style->background_color
    );
}

