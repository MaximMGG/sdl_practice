#include <SDL2/SDL.h>
#include <stdlib.h>

#define TEXTURE_W 2000
#define TEXTURE_H 2000
#define SCREEN_W 1000
#define SCREEN_H 1000

int main() {

    SDL_Rect source = {0, 0, SCREEN_W / 32, SCREEN_H / 32};
    SDL_Rect dest = {10, 10, SCREEN_W - 20, SCREEN_H - 20};
    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Scrolling",
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_W, SCREEN_H, 0);
    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, 
                                        SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H);
    SDL_Point pv[1000];

    for(int i = 0; i < 1000; i++) {
        SDL_Point p = {rand() % TEXTURE_H, rand() % TEXTURE_W};
        pv[i] = p;
    }

    int run = 1;

    while(run) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = 0;
            }
            if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP: source.y -= 3; break;
                    case SDLK_DOWN: source.y += 3; break;
                    case SDLK_LEFT: source.x -= 3; break;
                    case SDLK_RIGHT: source.x += 3; break;
                    case SDLK_1: source.w *= 2; source.h *= 2; break;
                    case SDLK_2: source.w /= 2; source.h /= 2; break;
                }
            }
        }

        SDL_SetRenderTarget(rend, texture);
        SDL_SetRenderDrawColor(rend, 0xFF, 0xFF,0xFF,0xFF);
        SDL_RenderClear(rend);

        for(int i = 0; i < 1000; i++) {
            pv[i].x += rand() % 3 - 1;
            pv[i].y += rand() % 3 - 1;
        }

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderDrawPoints(rend, pv, 1000);

        SDL_SetRenderTarget(rend, NULL);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, texture, &source, &dest);
        SDL_RenderPresent(rend);

        SDL_Delay(50);
    }
    SDL_Quit();
    return 0;
}
