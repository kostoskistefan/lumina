/**
 * @file:      main.c
 *
 * @date:      13 June 2024
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2024 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "lumina.h" // IWYU pragma: keep
#include "dev_font.h"
#include "dev_symbol_font.h"
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>

#define LUMINA_SCREEN_WIDTH  500
#define LUMINA_SCREEN_HEIGHT 500

xcb_gcontext_t gc;
xcb_image_t *image;
xcb_window_t window;
xcb_screen_t *xcb_screen;
xcb_connection_t *connection;

void render_callback(void)
{
    lumina_graphics_render_line(
        (lumina_point_t) { 10, 10 },
        (lumina_point_t) { 490, 490 },
        (lumina_line_style_t) { .color = 0x000000 }
    );

    lumina_graphics_render_line(
        (lumina_point_t) { 490, 10 },
        (lumina_point_t) { 10, 490 },
        (lumina_line_style_t) { .color = 0x000000 }
    );

    lumina_graphics_render_rectangle(
        (lumina_point_t) { 10, 10 },
        (lumina_size_t) { 480, 480 },
        (lumina_rectangle_style_t) { .color = 0x000000, .fill = false, .corner_radius = 24 }
    );

    lumina_graphics_render_circle(
        (lumina_point_t) { 250, 250 },
        100,
        (lumina_circle_style_t) { .color = 0x000000, .fill = false }
    );

    lumina_graphics_render_text_aligned(
        "Symbols",
        (lumina_point_t) { 250, 20 },
        &dev_font,
        (lumina_font_style_t) { .text_color = 0x000000, .background_color = 0xffffff },
        LUMINA_TEXT_ALIGNMENT_CENTER
    );

    lumina_graphics_render_text_aligned(
        LUMINA_FONT_GLYPH_F00C
        LUMINA_FONT_GLYPH_20
        LUMINA_FONT_GLYPH_F04D,
        (lumina_point_t) { 250, 35 },
        &dev_symbol_font,
        (lumina_font_style_t) { .text_color = 0x000000, .background_color = 0xffffff },
        LUMINA_TEXT_ALIGNMENT_CENTER
    );

    xcb_image_put(connection, window, gc, image, 0, 0, 0);
    xcb_flush(connection);
}

void demo_create_window(void);

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    demo_create_window();

    return 0;
}

void lumina_pixel_set(const uint16_t x, const uint16_t y, const lumina_color_t color)
{
    xcb_image_put_pixel(image, x, y, color);

    // Slow down the rendering to see it in action
    // xcb_image_put(connection, window, gc, image, 0, 0, 0);
    // usleep(10000);
    // xcb_flush(connection);
}

void demo_create_window(void)
{
    connection = xcb_connect(NULL, NULL);
    xcb_screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

    if (xcb_connection_has_error(connection))
    {
        fprintf(stderr, "Failed to connect to X server\n");
        exit(EXIT_FAILURE);
    }

    gc = xcb_generate_id(connection);
    window = xcb_generate_id(connection);

    xcb_create_window(
        connection,
        xcb_screen->root_depth,
        window,
        xcb_screen->root,
        0,
        0,
        LUMINA_SCREEN_WIDTH,
        LUMINA_SCREEN_HEIGHT,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        xcb_screen->root_visual,
        XCB_CW_EVENT_MASK,
        (uint32_t[]) { XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS }
    );

    xcb_create_gc(connection, gc, window, 0, NULL);

    uint8_t *image_data = malloc(LUMINA_SCREEN_WIDTH * LUMINA_SCREEN_HEIGHT * sizeof(uint32_t));

    memset(image_data, 0xff, LUMINA_SCREEN_WIDTH * LUMINA_SCREEN_HEIGHT * sizeof(uint32_t));

    if (image_data == 0)
    {
        fprintf(stderr, "Error: Failed to allocate memory for image data.\n");
    }

    image =
        xcb_image_create_native(
            connection,
            LUMINA_SCREEN_WIDTH,
            LUMINA_SCREEN_HEIGHT,
            XCB_IMAGE_FORMAT_Z_PIXMAP,
            xcb_screen->root_depth,
            NULL,
            UINT32_MAX,
            image_data
        );

    xcb_map_window(connection, window);
    xcb_flush(connection);

    xcb_generic_event_t *event;
    while ((event = xcb_wait_for_event(connection)))
    {
        if (event->response_type == XCB_EXPOSE)
        {
            render_callback();
        }

        free(event);
    }

    xcb_image_destroy(image);
    free(image_data);
    xcb_free_gc(connection, gc);
    xcb_destroy_window(connection, window);
    xcb_disconnect(connection);
}
