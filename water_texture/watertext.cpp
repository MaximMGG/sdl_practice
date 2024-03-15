#include <SDL2/SDL.h>
#include <iostream>


constexpr int WIDTH {640};
constexpr int HEIGHT {480};



int main() {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("SDL2 water", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *sur = SDL_LoadBMP("./pool2.bmp");
    SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 0xFF, 0, 0xFF));

    SDL_Texture *tex1 = SDL_CreateTextureFromSurface(rend, sur);
    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(rend, sur);

    SDL_FreeSurface(sur);

    SDL_Rect rect1 {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    SDL_Rect rect2 {.x = WIDTH - WIDTH * 2 + 1, .y = 0, .w = WIDTH, .h = HEIGHT};


    bool run = true;
    SDL_Event e;

    while(run) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = false;
            }
        }


        SDL_SetTextureBlendMode(tex1, SDL_BLENDMODE_NONE);
        SDL_RenderCopy(rend, tex1, NULL, &rect1);
        SDL_RenderCopy(rend, tex1, NULL, &rect2);

        SDL_RenderPresent(rend);

    }

    SDL_SetRenderDrawColor(rend, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(rend);

    int w, h;
    SDL_QueryTexture(tex1, NULL, NULL, &w, &h);
    SDL_Delay(20);


    rect2.x++;
    if (rect2.x == 0) {
        rect2.x = -639;
    }


    SDL_DestroyTexture(tex1);
    SDL_DestroyTexture(tex2);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    return 0;
}
