/**
 * @file:      lumina_text.h
 *
 * @date:      16 July 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#pragma once

#include "lumina_font.h"
#include "lumina_point.h"

/**
 * @enum lumina_text_alignment_t
 * @brief Text alignment
 */
typedef enum lumina_text_alignment_t
{
    LUMINA_TEXT_ALIGNMENT_LEFT,
    LUMINA_TEXT_ALIGNMENT_CENTER,
    LUMINA_TEXT_ALIGNMENT_RIGHT
} lumina_text_alignment_t;

/**
 * @brief Render text
 *
 * @param text The text to render
 * @param position The position of the text
 * @param font The font to use
 * @param style The font style
 */
void lumina_graphics_render_text(
    const char *text,
    const lumina_point_t position,
    const lumina_font_t *font,
    const lumina_font_style_t style
);

/**
 * @brief Render aligned text
 *
 * @param text The text to render
 * @param position The position of the text
 * @param font The font to use
 * @param style The font style
 * @param alignment The text alignment
 */
void lumina_graphics_render_text_aligned(
    const char *text,
    const lumina_point_t position,
    const lumina_font_t *font,
    const lumina_font_style_t style,
    const lumina_text_alignment_t alignment
);
