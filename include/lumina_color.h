#pragma once

#include <stdint.h>

typedef uint32_t lumina_color_t;

lumina_color_t lumina_color_blend(const lumina_color_t color1, const lumina_color_t color2, const float blend_factor);
