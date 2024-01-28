#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "mtext.h"
#include "app.h"

#define WIDTH 640 
#define HEIGHT 480 


LTexture *gFooTexture;
LTexture *gBackGroundTexture;

boolean init(App *app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_ERR("Error init sdl %s\n");
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            SDL_ERR("Set hint error %s\n");
        }
        app->win = SDL_CreateWindow(    "Color image", 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (app->win == NULL) {
            SDL_ERR("Create window error %s\n");
        } else {
            app->rend = SDL_CreateRenderer(app->win, -1, SDL_RENDERER_ACCELERATED);
            if (app->rend == NULL) {
                SDL_ERR("Create renderer error %s\n");
            } else {
                SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF,0xFF,0xFF);

                int imageFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imageFlags) & imageFlags)) {
                    IMG_ERR("Init image error %s\n");
                }
            }
        }
    }
    return true;
}

boolean load_media(App *app) {
    load_from_file(app, gFooTexture, "foo.png");

    if (gFooTexture == NULL) {
        printf("Fail to load texture\n");
    }

    load_from_file(app, gBackGroundTexture, "background.png");
    if (gBackGroundTexture == NULL) {
        printf("Fail to load texture\n");
    }
    return true;
}

void destroy(App *app) {
    free_Tex(gFooTexture);
    free_Tex(gBackGroundTexture);

    SDL_DestroyRenderer(app->rend);
    SDL_DestroyWindow(app->win);
    free(app);

    SDL_Quit();
    IMG_Quit();

}


int main() {
    gFooTexture = new_Tex();
    gBackGroundTexture = new_Tex();
    App *app = (App *) malloc(sizeof(App));
    init(app);
    load_media(app);
    
    boolean quit = false;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(app->rend);

        render(app, gBackGroundTexture, 0, 0);

        render(app, gFooTexture, 240, 190);
        SDL_RenderPresent(app->rend);
    }

    destroy(app);

    return 0;
}
