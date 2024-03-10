#include "lumina_style.h"

extern lumina_style_t _lumina_style;

void lumina_style_set_font(const lumina_font_t *const font)
{
    _lumina_style.font = font;
}

void lumina_style_set_line_color(const lumina_color_t color)
{
    _lumina_style.line_color = color;
}

void lumina_style_set_fill_color(const lumina_color_t color)
{
    _lumina_style.fill_color = color;
}

void lumina_style_set_compositing_color_interior(const lumina_color_t color)
{
    _lumina_style.compositing_color_interior = color;
}

void lumina_style_set_compositing_color_exterior(const lumina_color_t color)
{
    _lumina_style.compositing_color_exterior = color;
}

void lumina_style_set_compositing_mode(const lumina_style_compositing_mode_t mode)
{
    _lumina_style.compositing_mode = mode;
}
