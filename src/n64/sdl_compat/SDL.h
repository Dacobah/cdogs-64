/*
    Minimal SDL2 compatibility layer for Nintendo 64 (Libdragon)
*/
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libdragon.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef uint64_t Uint64;
typedef int8_t Sint8;
typedef int16_t Sint16;
typedef int32_t Sint32;
typedef int64_t Sint64;

#define SDL_BIG_ENDIAN 4321
#define SDL_LIL_ENDIAN 1234
#define SDL_BYTEORDER SDL_BIG_ENDIAN

#define SDL_Swap16(x) __builtin_bswap16(x)
#define SDL_Swap32(x) __builtin_bswap32(x)
#define SDL_Swap64(x) __builtin_bswap64(x)

#define SDL_PIXELFORMAT_UNKNOWN      0
#define SDL_PIXELFORMAT_RGB565       1
#define SDL_PIXELFORMAT_RGBA5551     2
#define SDL_PIXELFORMAT_RGBA8888     3
#define SDL_PIXELFORMAT_ARGB8888     4

typedef struct SDL_Point {
    int x;
    int y;
} SDL_Point;

typedef struct SDL_Rect {
    int x, y;
    int w, h;
} SDL_Rect;

typedef struct SDL_Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} SDL_Color;

typedef struct SDL_PixelFormat {
    Uint32 format;
    Uint8 BitsPerPixel;
    Uint8 BytesPerPixel;
    Uint32 Rmask, Gmask, Bmask, Amask;
    Uint8 Rshift, Gshift, Bshift, Ashift;
} SDL_PixelFormat;

typedef struct SDL_Surface {
    int w, h;
    int pitch;
    void *pixels;
    SDL_PixelFormat *format;
    void *userdata;
} SDL_Surface;

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture {
    int w, h;
    void *driverdata;
} SDL_Texture;

/* Audio stubs */
typedef struct Mix_Chunk Mix_Chunk;
typedef struct Mix_Music Mix_Music;

typedef enum {
    SDL_FLIP_NONE = 0x00000000,
    SDL_FLIP_HORIZONTAL = 0x00000001,
    SDL_FLIP_VERTICAL = 0x00000002
} SDL_RendererFlip;

typedef enum {
    SDL_BLENDMODE_NONE = 0x00000000,
    SDL_BLENDMODE_BLEND = 0x00000001,
    SDL_BLENDMODE_ADD = 0x00000002,
    SDL_BLENDMODE_MOD = 0x00000004
} SDL_BlendMode;

typedef enum {
    SDL_TEXTUREACCESS_STATIC,
    SDL_TEXTUREACCESS_STREAMING,
    SDL_TEXTUREACCESS_TARGET
} SDL_TextureAccess;

/* Timing */
static inline Uint32 SDL_GetTicks(void) {
    return (Uint32)TICKS_TO_MS(TICKS_READ());
}
static inline void SDL_Delay(Uint32 ms) {
    wait_ms(ms);
}

/* Scancodes & Keycodes (stubs for menu/keys) */
typedef enum {
    SDL_SCANCODE_UNKNOWN = 0,
    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,
    SDL_SCANCODE_UP = 82,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_F1 = 58,
    SDL_SCANCODE_F2 = 59,
    SDL_SCANCODE_F3 = 60,
    SDL_SCANCODE_F4 = 61,
    SDL_SCANCODE_F5 = 62,
    SDL_SCANCODE_F6 = 63,
    SDL_SCANCODE_F7 = 64,
    SDL_SCANCODE_F8 = 65,
    SDL_SCANCODE_F9 = 66,
    SDL_SCANCODE_F10 = 67,
    SDL_SCANCODE_F11 = 68,
    SDL_SCANCODE_F12 = 69
} SDL_Scancode;

typedef Sint32 SDL_Keycode;
#define SDLK_UNKNOWN 0
#define SDLK_RETURN '\r'
#define SDLK_ESCAPE '\033'
#define SDLK_BACKSPACE '\b'
#define SDLK_SPACE ' '

/* Events */
#define SDL_QUIT 0x100
#define SDL_KEYDOWN 0x300
#define SDL_KEYUP 0x301
#define SDL_DROPFILE 0x1000
#define SDL_DISABLE 0
#define SDL_ENABLE 1

typedef struct SDL_KeyboardEvent {
    Uint32 type;
    struct {
        SDL_Scancode scancode;
        SDL_Keycode sym;
    } keysym;
    Uint8 state;
    Uint8 repeat;
} SDL_KeyboardEvent;

typedef union SDL_Event {
    Uint32 type;
    SDL_KeyboardEvent key;
} SDL_Event;

static inline int SDL_PollEvent(SDL_Event *event) {
    (void)event;
    return 0;
}
static inline Uint8 SDL_EventState(Uint32 type, int state) {
    (void)type; (void)state;
    return 0;
}

/* Init / Quit */
#define SDL_INIT_TIMER          0x00000001u
#define SDL_INIT_AUDIO          0x00000010u
#define SDL_INIT_VIDEO          0x00000020u
#define SDL_INIT_JOYSTICK       0x00000200u
#define SDL_INIT_HAPTIC         0x00001000u
#define SDL_INIT_GAMECONTROLLER 0x00002000u
#define SDL_INIT_EVENTS         0x00004000u

static inline int SDL_Init(Uint32 flags) {
    (void)flags;
    return 0;
}
static inline void SDL_Quit(void) {}
static inline const char *SDL_GetError(void) { return ""; }

/* Stubs for Surface memory */
static inline int SDL_LockSurface(SDL_Surface *s) { (void)s; return 0; }
static inline void SDL_UnlockSurface(SDL_Surface *s) { (void)s; }
static inline void SDL_FreeSurface(SDL_Surface *s) {
    if (s) {
        if (s->format) free(s->format);
        if (s->pixels) free(s->pixels);
        free(s);
    }
}
static inline SDL_Surface *SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth,
                                               Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
    (void)flags;
    SDL_Surface *s = (SDL_Surface *)calloc(1, sizeof(SDL_Surface));
    s->w = width;
    s->h = height;
    s->format = (SDL_PixelFormat *)calloc(1, sizeof(SDL_PixelFormat));
    s->format->BitsPerPixel = depth;
    s->format->BytesPerPixel = depth / 8;
    s->format->Rmask = Rmask;
    s->format->Gmask = Gmask;
    s->format->Bmask = Bmask;
    s->format->Amask = Amask;
    s->pitch = width * (depth / 8);
    s->pixels = calloc(1, s->pitch * height);
    return s;
}

#ifdef __cplusplus
}
#endif
