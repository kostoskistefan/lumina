/**
 * @file:      lumina_utf8.c
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina_utf8.h"
#include <string.h>

static inline lumina_uint8_t lumina_utf8_byte_get_count(const lumina_char_t character)
{
    if ((character & 0x80) == 0x00)
    {
        return 1;
    }

    if ((character & 0xE0) == 0xC0)
    {
        return 2;
    }

    if ((character & 0xF0) == 0xE0)
    {
        return 3;
    }

    if ((character & 0xF8) == 0xF0)
    {
        return 4;
    }

    return 0; // Invalid byte
}

static lumina_utf8_unicode_codepoint_t lumina_utf8_to_unicode_codepoint(
    const lumina_char_t *const string,
    const lumina_uint8_t byte_count
)
{
    switch (byte_count)
    {
        case 1:
            return string[0] & 0x7F;

        case 2:
            return (string[0] & 0x1F) << 6 | (string[1] & 0x3F);

        case 3:
            return (string[0] & 0x0F) << 12 | (string[1] & 0x3F) << 6 | (string[2] & 0x3F);

        case 4:
            return (string[0] & 0x07) << 18 | (string[1] & 0x3F) << 12 | (string[2] & 0x3F) << 6 | (string[3] & 0x3F);

        default:
            return 0;
    }
}

lumina_utf8_iterator_t lumina_utf8_iterator_create(const lumina_char_t *const string)
{
    return (lumina_utf8_iterator_t) {
        .current = string,
        .end = (string == NULL) ? NULL : (string + strlen(string))
    };
}

lumina_utf8_unicode_codepoint_t lumina_utf8_iterator_next(lumina_utf8_iterator_t *const iterator)
{
    if (iterator == NULL || iterator->current >= iterator->end)
    {
        return 0;
    }

    const lumina_uint8_t byte_count = lumina_utf8_byte_get_count(*iterator->current);

    if (byte_count == 0 || iterator->current + byte_count > iterator->end)
    {
        return 0;
    }

    const lumina_utf8_unicode_codepoint_t codepoint = lumina_utf8_to_unicode_codepoint(iterator->current, byte_count);

    iterator->current += byte_count;

    return codepoint;
}

lumina_int_t lumina_utf8_unicode_codepoint_compare(const void *const a, const void *const b)
{
    return *(const lumina_utf8_unicode_codepoint_t *) a - *(const lumina_utf8_unicode_codepoint_t *) b;
}
