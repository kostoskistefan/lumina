/**
 * @file:      lumina_types.h
 *
 * @date:      22 November 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef LUMINA_TYPES_H
#define LUMINA_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef bool lumina_bool_t;

typedef char lumina_char_t;

typedef int lumina_int_t;

typedef float lumina_float_t;

typedef int8_t lumina_int8_t;
typedef int16_t lumina_int16_t;
typedef int32_t lumina_int32_t;

typedef uint8_t lumina_uint8_t;
typedef uint16_t lumina_uint16_t;
typedef uint32_t lumina_uint32_t;

#ifdef __cplusplus
}
#endif

#endif // LUMINA_TYPES_H
