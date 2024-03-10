#pragma once

#include <stdint.h>

typedef enum lumina_text_alignment_t
{
    LUMINA_TEXT_ALIGN_LEFT,
    LUMINA_TEXT_ALIGN_CENTER,
    LUMINA_TEXT_ALIGN_RIGHT,
} lumina_text_alignment_t;

void lumina_render_vertical_line(const uint16_t x, const uint16_t y, const uint16_t length);
void lumina_render_horizontal_line(const uint16_t x, const uint16_t y, const uint16_t length);

void lumina_render_circle_outline(const uint16_t x, const uint16_t y, const uint16_t radius);
void lumina_render_circle_filled(const uint16_t x, const uint16_t y, const uint16_t radius);

void lumina_render_rectangle_outline(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);
void lumina_render_rectangle_filled(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);

void lumina_render_rounded_rectangle_outline(
    const uint16_t x,
    const uint16_t y,
    const uint16_t width,
    const uint16_t height,
    const uint16_t radius
);

void lumina_render_rounded_rectangle_filled(
    const uint16_t x,
    const uint16_t y,
    const uint16_t width,
    const uint16_t height,
    const uint16_t radius
);

void lumina_render_character(const uint16_t x, const uint16_t y, const char character);
void lumina_render_text(const uint16_t x, const uint16_t y, const char* text);
void lumina_render_text_aligned(const uint16_t x, const uint16_t y, const char* text, const lumina_text_alignment_t alignment);
