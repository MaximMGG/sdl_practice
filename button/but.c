#include <SDL2/SDL.h>
#include <stdio.h>

#define W_WIDTH 800
#define W_HEIGHT 600
typedef char bool;
#define true 1
#define false 0

typedef struct {
    int x, y;
} mouse_pos;

typedef struct {
    int r, g, b;
} rgb;

typedef struct {
    rgb color;
    int x, y;
    int w, h;
    char *text;
} SDL_Button;

bool SDL_RenderDrawButton(SDL_Button *button, SDL_Renderer *rend) {

    return 0;
}


bool SDL_AttachButton(SDL_Button *button, mouse_pos *p) {

    return 0;
}

bool mouse_in_rect(SDL_Rect *r, int x, int y) {
    return (x >= r->x && x <= r->w + r->x) && (y >= r->y && y <= r->h + r->y);
}

int main() {

    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("But", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0xFF);
    SDL_RenderClear(rend);

    SDL_Rect but;
    but.x = 100;
    but.y = 100;
    but.w = 20;
    but.h = 20;
    int but_r = 0;
    int but_g = 255;
    int but_b = 255;


    int x = 0, y = 0;


    bool quit = false;
    SDL_Event e;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_GetMouseState(&x, &y);


        SDL_SetRenderDrawColor(rend, but_r, but_g, but_b, 0xFF);
        SDL_RenderFillRect(rend, &but);
        SDL_RenderPresent(rend);

        if (mouse_in_rect(&but, x, y)) {
            but_r = 255;
        } else {
            but_r = 0;

        }



        SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
