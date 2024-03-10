#include "lumina_color.h"

lumina_color_t lumina_color_blend(const lumina_color_t color1, const lumina_color_t color2, const float blend_factor)
{
    if (blend_factor <= 0.0f)
    {
        return color1;
    }

    if (blend_factor >= 1.0f)
    {
        return color2;
    }

    const uint8_t red1 = (color1 >> 16) & 0xff;
    const uint8_t green1 = (color1 >> 8) & 0xff;
    const uint8_t blue1 = color1 & 0xff;

    const uint8_t red2 = (color2 >> 16) & 0xff;
    const uint8_t green2 = (color2 >> 8) & 0xff;
    const uint8_t blue2 = color2 & 0xff;

    const uint8_t red_blend = red1 + (red2 - red1) * blend_factor;
    const uint8_t green_blend = green1 + (green2 - green1) * blend_factor;
    const uint8_t blue_blend = blue1 + (blue2 - blue1) * blend_factor;

    return (red_blend << 16) | (green_blend << 8) | blue_blend;
}
