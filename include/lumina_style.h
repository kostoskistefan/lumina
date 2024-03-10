
#pragma once

#include <stdbool.h>
#include "lumina_font.h"
#include "lumina_color.h"

typedef enum lumina_style_compositing_mode_t
{
    LUMINA_STYLE_COMPOSITING_MODE_AUTO,
    LUMINA_STYLE_COMPOSITING_MODE_MANUAL
} lumina_style_compositing_mode_t;

typedef struct lumina_style_t
{
    const lumina_font_t *font;
    lumina_color_t line_color;
    lumina_color_t fill_color;
    lumina_color_t compositing_color_interior;
    lumina_color_t compositing_color_exterior;
    lumina_style_compositing_mode_t compositing_mode;
} lumina_style_t;

void lumina_style_set_font(const lumina_font_t *const font);
void lumina_style_set_line_color(const lumina_color_t color);
void lumina_style_set_fill_color(const lumina_color_t color);
void lumina_style_set_compositing_color_interior(const lumina_color_t color);
void lumina_style_set_compositing_color_exterior(const lumina_color_t color);
void lumina_style_set_compositing_mode(const lumina_style_compositing_mode_t mode);

static inline void lumina_style_set_compositing_color(const lumina_color_t color)
{
    lumina_style_set_compositing_color_interior(color);
    lumina_style_set_compositing_color_exterior(color);
}
