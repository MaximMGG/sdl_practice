#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define P_ERR(m)   fprintf(stderr, "%s - %s\n", m, SDL_GetError())
#define WIDTH 1000
#define HEIGHT 600


typedef struct {
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Surface *strech;
    SDL_Surface *screen;
    SDL_Surface *load;
} App;


SDL_Surface *loadSurface(App *app, char *path) {

    SDL_Surface *opt = NULL;

    SDL_Surface *loads = SDL_LoadBMP(path);
    if (loads == NULL) {
        P_ERR("Load surface error");
    } else {
        opt = SDL_ConvertSurface(loads, app->screen->format, 0);
    }

    SDL_FreeSurface(loads);


    return opt;
}

int loadMedia(App *app) {
    
    app->strech = loadSurface(app, "press.bmp");
    if (app->strech == NULL) {
        P_ERR("Load image error");
        return -1;
    }

    return 0;
}

int init(App *app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        P_ERR("Init error");
    }

    app->win = SDL_CreateWindow("Key pressed", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED,
                                WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (app->win == NULL) {
        P_ERR("Create window error");
        return -1;
    } else {
        app->screen = SDL_GetWindowSurface(app->win);
    }

    return 0;
}

void end_work(App *app) {
    SDL_DestroyWindow(app->win);
    SDL_Quit();

    free(app);
}


int main() {
    App *app = (App *) malloc(sizeof(App));
    init(app);
    loadMedia(app);

    SDL_Event e;
    int quit = 1;
    while (quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 0;
            }
        }
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = WIDTH;
        stretchRect.h = HEIGHT;
        SDL_BlitScaled(app->strech, NULL, app->screen, &stretchRect);
        SDL_UpdateWindowSurface(app->win);

    }

    end_work(app);
    return 0;
}
