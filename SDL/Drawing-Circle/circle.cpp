#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <queue>


namespace SDL
{
    SDL_DisplayMode dm;

    SDL_Window *win = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;

    void init()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GetCurrentDisplayMode(0, &dm);
        win = SDL_CreateWindow("Default", 0, 0, dm.w, dm.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

        renderer = SDL_CreateRenderer(win, -1, ::SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        texture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(win), ::SDL_TEXTUREACCESS_STATIC, dm.w, dm.h);
        SDL_Delay(1000);
    }

    void exit()
    {
        SDL_DestroyWindow(win);
        win = nullptr;

        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        SDL_DestroyTexture(texture);
        texture = nullptr;

        SDL_Quit();
    }
};




inline Uint32 Area(Uint32 x, Uint32 a, Uint32 b, Uint32 R)
{
    return (x - a) * (sqrt(R * R - x * x) - b); // Area of the Rectangle wrt the new origin a, b;
}

Uint32 maximize_area(Uint32 a, Uint32 b, Uint32 R) // performs ternary search to find the maximum.
{
    Uint32 l = a, r = sqrt(R * R - b * b);

    Uint32 q, Aq, p, Ap;

    while (l < r)
    {
        q = l + (r - l) / 3;
        Aq = Area(q, a, b, R);

        p = r - (r - l) / 3;
        Ap = Area(p, a, b, R);

        if (Aq > Ap)
            r = p - 1;
        else
            l = q + 1;
    }
    return l;
}

std::queue<std::pair<Uint32, Uint32>> Q;


void draw_circle(Uint32 x, Uint32 y, Uint32 R) // x and y must be greater than R 
{
    Uint32 a = 0, b = 0;
    Uint32 p, q;
    SDL_Rect r;


    SDL_SetRenderDrawColor(SDL::renderer, 200, 0, 0, 255);
    SDL_SetRenderDrawBlendMode(SDL::renderer, ::SDL_BLENDMODE_BLEND);

    p = maximize_area(a, b, R);
    q = sqrt(R*R - p*p);
    r.x = x - p;
    r.y = y - q;
    r.w = 2*p;
    r.h = 2*q;
    SDL_RenderFillRect(SDL::renderer, &r);


    Q.push(std::make_pair(p, 0));
    
    while(!Q.empty()) 
    // Careful here. May result in Infinite loop. 
    // Since interger arithmetic is used. smaller values approximate and result in repetitions.
    // OR condition prevents it.
    // Even for Bigger Circles 500-600px it draws only about 100 rects
    {
        a = Q.front().first;
        b = Q.front().second;
        Q.pop();
        
        // with a and b as out new origin find the rectangle with maximum area that can be inscribed in our circle
        p = maximize_area(a, b, R); 
        q = sqrt(R * R - p * p);

        r.x = x + a;
        r.y = y - q;
        r.w = p - a;
        r.h = q - b;


        if (!(r.w && r.h))
            continue;

        SDL_RenderFillRect(SDL::renderer, &r);

        Q.push(std::make_pair(a, q));
        Q.push(std::make_pair(p, b));
    }

    // For Anti-aliasing.

    for(double px = R/sqrt(2); px <= R; px += 0.1)
    {
        double py = sqrt(R*R - px*px);

        SDL_SetRenderDrawColor(SDL::renderer, 200, 0, 0, 50);
        r.x = px + x - 1;
        r.y = y - py - 1;
        r.w = 3;
        r.h = 3;

        SDL_RenderDrawRect(SDL::renderer, &r);
    }

    SDL_RenderPresent(SDL::renderer);
}



int main(int argc, char **argv)
{
    SDL_Event event;

    SDL::init();

    draw_circle(500, 500, 300);

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
