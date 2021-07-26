#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "benchmark.h"

/* Results
 6-7ms per run()
*/

inline uint32_t ARGB(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
{
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

//Marsaglia's xorshf generator (Fast Random Function)
static uint32_t s_randX = 123456789;
static uint32_t s_randY = 362436069;
static uint32_t s_randZ = 521288629;

inline uint32_t FastRand(void)
{
    uint32_t t;

    s_randX ^= s_randX << 16;
    s_randX ^= s_randX >> 5;
    s_randX ^= s_randX << 1;

    t = s_randX;
    s_randX = s_randY;
    s_randY = s_randZ;
    s_randZ = t ^ s_randX ^ s_randY;

    return s_randZ;
}

namespace SDL
{
    SDL_DisplayMode dm;

    SDL_Window *win = nullptr;
    SDL_Surface *wsurface = nullptr;

    Uint32 *pixels = nullptr;

    void init()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GetCurrentDisplayMode(0, &dm);
        win = SDL_CreateWindow("Default", 0, 0, dm.w, dm.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        wsurface = SDL_GetWindowSurface(win);
        pixels = static_cast<Uint32*>(wsurface->pixels);
        SDL_Delay(1000);
    }

    void exit()
    {
        SDL_DestroyWindow(win);
        win = nullptr;

        SDL_Quit();
        IMG_Quit();
    }

    void run()
    {
        for (int i = 0; i < dm.w * dm.h; ++i)
        {
            pixels[i] = ARGB(FastRand() % 256, FastRand() % 256, FastRand() % 256, 255);
        }
        SDL_UpdateWindowSurface(win);
    }
};

int main(int argc, char **argv)
{
    SDL_Event event;

    SDL::init();

    benchmark(100, SDL::run);

    while (1)
    {
        while ((SDL_PollEvent(&event) != 0))
        {
            if (event.type == SDL_QUIT)
            {
                SDL::exit();
                return 0;
            }
        }
        SDL_Delay(50);
    }
    return 0;
}
