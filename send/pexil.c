#include <SDL2/SDL.h>
#include <stdio.h>


#define WIDTH 720
#define HEIGHT 480

int main () {

    SDL_Window *win;
    SDL_Renderer *rend;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Pixel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!win) {
        SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    }

    SDL_Event e;
    int run = 1;

    while(run) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = 0;
            }
        }

        SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 0xAF, 0x0F, 0xFF, 0x00);
        SDL_RenderDrawPoint(rend, 100, 100);

        SDL_Rect r = {.x = 40, .y = 40, .h = 40, .w = 40};

        SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(rend, &r);



        SDL_RenderPresent(rend);
    }


    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    return 0;
}
