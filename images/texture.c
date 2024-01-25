#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    SDL_Texture *texture;
    SDL_Window *win;
    SDL_Renderer *rend;
} App;


void init(App *app) { 
    SDL_Init(SDL_INIT_VIDEO);

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        fprintf(stderr, "Error sdl hint render %s\n", SDL_GetError());
    };

    app->win = SDL_CreateWindow("Image window", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (app->win == NULL) {
        fprintf(stderr, "Error create window %s\n", SDL_GetError());        
    } else {
        app->rend = SDL_CreateRenderer(app->win, -1, SDL_RENDERER_ACCELERATED);
        if (app->rend == NULL) {
            fprintf(stderr, "Error create renderer %s\n", SDL_GetError());
        } else {
            SDL_SetRenderDrawColor(app->rend, 0xFF, 0xFF, 0xFF, 0xFF);

            int imageFlag = IMG_INIT_PNG;
            if (!(IMG_Init(imageFlag) & imageFlag)) {
                fprintf(stderr, "Init image error %s\n", IMG_GetError());
            }
        }
    }

}



SDL_Texture *load_texture(App *app, char *path) {

    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadSurface = IMG_Load(path);
    if (loadSurface == NULL) {
        fprintf(stderr, "Img load error %s\n", IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(app->rend, loadSurface);
        if (newTexture == NULL) {
            fprintf(stderr, "Create texture from surface error %s\n", SDL_GetError());
        }
    }

    SDL_FreeSurface(loadSurface);

    return newTexture;
}

void closed(App *app) {

    SDL_DestroyTexture(app->texture);
    SDL_DestroyRenderer(app->rend);
    SDL_DestroyWindow(app->win);

    IMG_Quit();
    SDL_Quit();

    free(app);
}

void loadMedia(App *app) {
    app->texture = load_texture(app, "texture.png");
    if (app->texture == NULL) {
        fprintf(stderr, "load texture error\n");
    }
}



int main() {
    App *app = (App *) malloc(sizeof(App));
    init(app);
    loadMedia(app);
    
    int quit = 1;
    SDL_Event e;

    while(quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 0;
            }
        }
        SDL_RenderClear(app->rend);
        SDL_RenderCopy(app->rend, app->texture, NULL, NULL);
        SDL_RenderPresent(app->rend);
    }

    closed(app);

    return 0;
}
