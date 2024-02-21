#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_ERR(a) fprintf(stderr, a, SDL_GetError());
#define IMG_ERR(a) fprintf(stderr, a, IMG_GetError());

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    SDL_Window *win;
    SDL_Renderer *rend;
} App;

int init(App *app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_ERR("Init error %s\n");
    } else {
        if ((app->win = SDL_CreateWindow(    "Rect app", 
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            WIDTH, HEIGHT,
                                            SDL_WINDOW_SHOWN)) == NULL) {
            SDL_ERR("Create window error %s\n");
        } else {
            app->rend = SDL_CreateRenderer(app->win, -1, SDL_RENDERER_ACCELERATED);
            if (app->rend == NULL) {
                SDL_ERR("Create renderer error %s\n");
            } else {
                SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return 0;
}

void closed(App *app) {
    SDL_DestroyRenderer(app->rend);
    SDL_DestroyWindow(app->win);

    free(app);
    SDL_Quit();
}

int main() {
    App *app = (App *) malloc(sizeof(App));

    init(app);
    int quit = 1;
    SDL_Event e;

    while(quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 0;
            }
        }

        SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(app->rend);

        SDL_Rect fillRect = {WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2};
        SDL_SetRenderDrawColor(app->rend, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(app->rend, &fillRect);


        // SDL_Rect outlineRect = {WIDTH / 6, HEIGHT / 6, WIDTH * 2 / 3, HEIGHT * 2 / 3};
        int distx = WIDTH / 6;
        int disty = HEIGHT / 6;
        SDL_Rect outlineRect = {distx, disty, WIDTH - distx * 2, HEIGHT - disty * 2};
        SDL_SetRenderDrawColor(app->rend, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(app->rend, &outlineRect);


        SDL_SetRenderDrawColor(app->rend, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(app->rend, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);

        //diagonal
        SDL_SetRenderDrawColor(app->rend, 0xFF, 0xAA, 0x00, 0xFF);
        SDL_RenderDrawLine(app->rend, 0, HEIGHT, WIDTH, 0);
        //diagonal 2
        SDL_SetRenderDrawColor(app->rend, 0x44, 0xAA, 0x00, 0xFF);
        int x = 0, y = 5;
        int xx = WIDTH - 5, yy = HEIGHT;
        for(int i = 0; i < 10; i++) {
            SDL_RenderDrawLine(app->rend, x, y, xx, yy);
            if (y > 0) {
                y--;
            } else {
                x++;
            }
            if (xx < WIDTH) {
                xx++;
            } else {
                yy--;
            }

        }

        SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF, 0x00, 0xFF);
        for(int i = 0; i < HEIGHT; i += 4) {
            SDL_RenderDrawPoint(app->rend, WIDTH / 2, i);
        }

        SDL_RenderPresent(app->rend);
    }
    closed(app);
    return 0;
}
