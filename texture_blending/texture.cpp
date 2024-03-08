#include <SDL2/SDL_error.h>
#include <iostream>
#include <SDL2/SDL.h>

constexpr int WIDTH {800};
constexpr int HEIGHT {600};


int main() {

    SDL_Window *win {};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initializec" << SDL_GetError() << '\n';
    } else {
        std::cout << "SDL video enabled\n";
    }

    win = SDL_CreateWindow("Texture win", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *sur = SDL_LoadBMP("./ft.bmp");

    SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 0xFF, 0, 0xFF));
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, sur);
    SDL_FreeSurface(sur);

    SDL_Rect rect {.x = 50, .y = 100, .w = 200, .h = 200};
    SDL_Rect rect2 {.x = 250, .y = 300, .w = 200, .h = 200};

    bool run =true;

    SDL_Event e;
    int x = 0, y = 0;
    while(run) {

        // while(SDL_HasEvent(!SDL_QUIT)) {
        //     if (e.type == SDL_QUIT) {
        //         run = false;
        //     }
        // }

        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = false;
            }
            if (e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&x, &y);
                rect2.x = e.motion.x;
                rect2.y = e.motion.y;
            }
        }

        SDL_SetRenderDrawColor(rend, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(rend, 5, 5, 200, 200);

        SDL_RenderCopy(rend, tex, NULL, &rect);
        SDL_RenderCopy(rend, tex, NULL, &rect2);


        SDL_RenderPresent(rend);

    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    return 0;
}
