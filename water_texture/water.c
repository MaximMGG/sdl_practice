#include <SDL2/SDL.h>
#include <stdio.h>

#define serror(msg) fprintf(stderr, "%s - %s\n", msg, SDL_GetError());

#define WIDTH 800
#define HEIGHT 600


int main() {
    SDL_Window *win;
    SDL_Renderer *rend;

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        serror("SDL no init");
    } else {
        win = SDL_CreateWindow("Waterbland", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (win == NULL) {
            serror("win not create");
        } else {
            rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
            if (rend == NULL) {
                serror("Renderer not create");
            }

            SDL_Surface *sur = SDL_LoadBMP("./pool.bmp");
            // SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 0xFF, 0, 0xFF));

            SDL_Texture *tex1 = SDL_CreateTextureFromSurface(rend, sur);
            SDL_Texture *tex2 = SDL_CreateTextureFromSurface(rend, sur);

            SDL_FreeSurface(sur);


            SDL_Rect rect1 = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
            SDL_Rect rect2 = {.x = -639, .y = 0, .w = WIDTH, .h = HEIGHT};
            SDL_Rect rect3 = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
            SDL_Rect rect4 = {.x = 0, .y = -480, .w = WIDTH, .h = HEIGHT};


            SDL_Event e;
            int run = 1;

            while(run) {
                while(SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        run = 0;
                    }
                }
            }

        }
    }




    return 0;
}
