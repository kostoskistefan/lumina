/**
 * @file:      lumina_utf8.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_UTF8_H
#define LUMINA_UTF8_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lumina_types.h"

typedef lumina_uint32_t lumina_utf8_unicode_codepoint_t;

typedef struct lumina_utf8_iterator_t
{
    const lumina_char_t *current;
    const lumina_char_t *end;
} lumina_utf8_iterator_t;

lumina_utf8_iterator_t lumina_utf8_iterator_create(const lumina_char_t *const string);
lumina_utf8_unicode_codepoint_t lumina_utf8_iterator_next(lumina_utf8_iterator_t *const iterator);

lumina_int_t lumina_utf8_unicode_codepoint_compare(const void *const a, const void *const b);

#ifdef __cplusplus
}
#endif

#endif // LUMINA_UTF8_H
