/**
 * @file:      lumina_label.c
 *
 * @date:      02 February 2025
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
#include <stddef.h>

static lumina_uint16_t lumina_label_get_alighment_offset(lumina_label_t *const label)
{
    if (label->text_alignment == LUMINA_TEXT_ALIGNMENT_LEFT)
    {
        return 0;
    }

    lumina_int16_t alighment_offset = 0;

    if (label->text_alignment == LUMINA_TEXT_ALIGNMENT_CENTER)
    {
        alighment_offset = label->_width >> 1;
    }

    else if (label->text_alignment == LUMINA_TEXT_ALIGNMENT_RIGHT)
    {
        alighment_offset = label->_width;
    }

    if (label->x < alighment_offset)
    {
        alighment_offset = label->x;
    }

    return alighment_offset;
}

void lumina_label_render(lumina_label_t *const label)
{
    if (label == NULL || label->text == NULL || label->font == NULL)
    {
        return;
    }

    if (label->_width == 0)
    {
        label->_width = lumina_text_get_width(label->text, label->font);
    }

    lumina_uint16_t alignment_offset = lumina_label_get_alighment_offset(label);

    // Clear previous text
    lumina_rectangle_filled_render(
        label->x - alignment_offset,
        label->y,
        label->_width,
        label->_height,
        0,
        label->background_color,
        label->background_color
    );

    // Recalculate dimensions for new text
    label->_width = lumina_text_get_width(label->text, label->font);
    label->_height = label->font->ascent + label->font->descent;

    alignment_offset = lumina_label_get_alighment_offset(label);

    // Render background
    lumina_rectangle_filled_render(
        label->x - alignment_offset,
        label->y,
        label->_width,
        label->_height,
        0,
        label->background_color,
        label->background_color
    );

    // Render text
    lumina_text_render(
        label->text,
        label->x,
        label->y,
        label->text_alignment,
        label->font,
        label->text_color,
        label->background_color
    );
}