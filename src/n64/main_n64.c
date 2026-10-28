/*
    C-Dogs 64 - Nintendo 64 Entry Point (Libdragon)
*/
#include <stdio.h>
#include <stdlib.h>
#include <libdragon.h>

int main(void)
{
    // Initialize debug console (ISViewer / USB)
    debug_init_isviewer();
    debug_init_usblog();

    // Initialize display: 320x240, 16-bit color, triple buffering
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE);

    // Initialize controllers
    joypad_init();

    // Initialize RDP queue
    rdpq_init();

    // Initialize DragonFS virtual filesystem
    if (dfs_init(DFS_DEFAULT_LOCATION) != DFS_ESUCCESS) {
        debugf("Warning: DFS init failed or no romfs attached\n");
    } else {
        debugf("DragonFS initialized successfully\n");
    }

    // Initialize timer
    timer_init();

    debugf("C-Dogs 64 booted successfully!\n");

    int frame = 0;
    while (1) {
        joypad_poll();
        joypad_buttons_t btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

        surface_t *disp = display_get();

        // Clear screen with a nice dark slate blue (C-Dogs style)
        rdpq_attach_clear(disp, NULL);

        // Simple animation to show the engine loop is running
        rdpq_set_mode_standard();
        rdpq_mode_combiner(RDPQ_COMBINER_FLAT);

        // Draw a colored status box
        rdpq_set_prim_color(RGBA32(0x30, 0x60, 0x90, 0xFF));
        rdpq_fill_rectangle(20, 20, 300, 220);

        rdpq_set_prim_color(RGBA32(0x18, 0x30, 0x50, 0xFF));
        rdpq_fill_rectangle(24, 24, 296, 216);

        // Moving indicator
        int x = 30 + ((frame * 2) % 240);
        rdpq_set_prim_color(btn.a ? RGBA32(0x00, 0xFF, 0x80, 0xFF) : RGBA32(0xFF, 0xAA, 0x00, 0xFF));
        rdpq_fill_rectangle(x, 110, x + 20, 130);

        rdpq_detach_show();

        frame++;
    }

    return 0;
}
