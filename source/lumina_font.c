/**
 * @file:      lumina_font.c
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_font.h"
#include <stdio.h>
#include <stdlib.h>

const lumina_font_glyph_data_t *lumina_font_get_glyph_data(
    const lumina_font_t *const font,
    const lumina_utf8_unicode_codepoint_t codepoint
)
{
    for (
        lumina_uint16_t character_map_index = 0;
        character_map_index < font->character_maps_count;
        ++character_map_index
    )
    {
        const lumina_font_character_map_t *const character_map = &font->character_maps[character_map_index];
        const lumina_utf8_unicode_codepoint_t relative_codepoint = codepoint - character_map->range_start;

        if (relative_codepoint >= character_map->range_length)
        {
            continue;
        }

        if (character_map->type == LUMINA_FONT_CHARACTER_MAP_TYPE_SEQUENTIAL)
        {
            return &font->glyph_data[character_map->glyph_bitmap_start_index + relative_codepoint];
        }

        if (character_map->type == LUMINA_FONT_CHARACTER_MAP_TYPE_SPARSE)
        {
            const lumina_utf8_unicode_codepoint_t *const codepoint_index =
                bsearch(
                    &codepoint,
                    character_map->unicode_codepoints,
                    character_map->unicode_codepoints_count,
                    sizeof(lumina_utf8_unicode_codepoint_t),
                    lumina_utf8_unicode_codepoint_compare
                );

            if (codepoint_index != NULL)
            {
                const lumina_utf8_unicode_codepoint_t index_offset = codepoint_index - character_map->unicode_codepoints;
                return &font->glyph_data[character_map->glyph_bitmap_start_index + index_offset];
            }
        }
    }

    return NULL;
}
