/**
 * @file:      lumina_font.c
 *
 * @date:      18 August 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the GNU General Public License version 3.
 *             For a copy, see <https://opensource.org/license/gpl-3-0/>.
 */

#include "lumina_font.h"

const lumina_font_glyph_metadata_t *lumina_font_get_glyph_metadata_from_character(
    const char character,
    const lumina_font_t *const font
)
{
    // Get the index of the glyph from the font's lookup table (LUT)
    uint8_t lut_index = character;

    if (font->indexing_mode == LUMINA_FONT_INDEXING_MODE_ASCII)
    {
        // Check if the character is definitely not in the font
        if (character < font->first_valid_index || character > font->last_valid_index)
        {
            return &font->glyph_metadata[0];
        }

        // Subtract the first valid index from the character to get the index of the glyph
        lut_index -= font->first_valid_index;
    }

    // Get the index of the glyph from the font's lookup table (LUT)
    const lumina_font_glyph_lut_entry_t font_glyph_index = font->glyph_lut[lut_index];

    // Get the metadata of the glyph
    return &font->glyph_metadata[font_glyph_index];
}
