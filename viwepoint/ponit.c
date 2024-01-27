#include <SDL2/SDL.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


#define WIDTH 800
#define HEIGHT 600
#define SDL_ERR(a) fprintf(stderr, a, SDL_GetError())
#define IMG_ERR(a) fprintf(stderr, a, IMG_GetError())

typedef struct {
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Texture *texture;
} App;

int init(App *app) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_ERR("Init sdl error %s\n");
        return -1;
    }

    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == 0) {
        SDL_ERR("set hint error %s\n");
    } 

    app->win = SDL_CreateWindow("Pointed window",   
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (app->win == NULL) {
        SDL_ERR("Create window error %s\n");
    } else {
        app->rend = SDL_CreateRenderer(app->win, -1, SDL_RENDERER_ACCELERATED);
        if (app->rend == NULL) {
            SDL_ERR("Render creatinon error %s\n");
        } else {
            SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF, 0xFF, 0xFF);



            int imgFlag = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlag) & imgFlag)) {
                IMG_ERR("Init img error %s\n");
            }
        }
    }
    return 0;
}

SDL_Texture *load_texture(App *app, char *path) {
    
    SDL_Texture *temp;
    SDL_Surface *temp_surf = IMG_Load(path);
    if (temp_surf == NULL) {
        IMG_ERR("Load image error %s\n");
    } else {
        temp = SDL_CreateTextureFromSurface(app->rend, temp_surf);
        if (temp == NULL) {
            IMG_ERR("create texture error %s\n");
        }

        SDL_FreeSurface(temp_surf);
    }

    return temp;
}


int load_media(App *app) {
    app->texture = load_texture(app, "viewport.png");
    return 0;
}

void destroy(App *app) {

    SDL_DestroyTexture(app->texture);
    SDL_DestroyRenderer(app->rend);
    SDL_DestroyWindow(app->win);

    IMG_Quit();
    SDL_Quit();

    free(app);
}


int main() {
    App *app = (App *) malloc(sizeof(App));

    init(app);
    load_media(app);

    int quit = 1;
    SDL_Event e;
    while(quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 0;
            }
        }

        SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF,0xFF,0xFF);
        SDL_RenderClear(app->rend);

        SDL_Rect topLeftViewPort;
        topLeftViewPort.x = 0;
        topLeftViewPort.y = 0;
        topLeftViewPort.w = WIDTH / 2;
        topLeftViewPort.h = HEIGHT / 2;
        SDL_RenderSetViewport(app->rend, &topLeftViewPort);

        SDL_RenderCopy(app->rend, app->texture, NULL, NULL);
        

        SDL_Rect topRightViewPort;
        topRightViewPort.x = WIDTH / 2;
        topRightViewPort.y = 0;
        topRightViewPort.w = WIDTH / 2;
        topRightViewPort.h = HEIGHT / 2;
        SDL_RenderSetViewport(app->rend, &topRightViewPort);
        SDL_RenderCopy(app->rend, app->texture, NULL, NULL);

        SDL_Rect bottomViewPort;
        bottomViewPort.x = 0;
        bottomViewPort.y = HEIGHT / 2;
        bottomViewPort.w = WIDTH;
        bottomViewPort.h = HEIGHT / 2;
        SDL_RenderSetViewport(app->rend, &bottomViewPort);
        SDL_RenderCopy(app->rend, app->texture, NULL, NULL);


        SDL_RenderPresent(app->rend);
    }


    destroy(app);


    return 0;
}
