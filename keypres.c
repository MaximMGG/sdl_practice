#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define P_ERR(m)   fprintf(stderr, "%s - %s\n", m, SDL_GetError())
#define WIDTH 1000
#define HEIGHT 600

enum KeyPress {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};


typedef struct {
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Surface *cur;
    SDL_Surface *screen;
    SDL_Surface *move[KEY_PRESS_SURFACE_TOTAL];
} App;


SDL_Surface *loadSurface(char *path) {

    SDL_Surface *sur = SDL_LoadBMP(path);
    if (sur == NULL) {
        P_ERR("Surface create error");
        return NULL;
    }

    return sur;
}

int loadMedia(App *app) {
    
    app->move[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
    app->move[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
    app->move[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
    app->move[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
    app->move[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");

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
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        SDL_FreeSurface(app->move[i]);
        app->move[i] = NULL;
    }
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
    app->cur = app->move[KEY_PRESS_SURFACE_DEFAULT];
    while(quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 0;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        app->cur = app->move[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        app->cur = app->move[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        app->cur = app->move[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        app->cur = app->move[KEY_PRESS_SURFACE_RIGHT];
                        break;
                }
            }
        }
        SDL_BlitSurface(app->cur, NULL, app->screen, NULL);
        SDL_UpdateWindowSurface(app->win);
    }

    end_work(app);
    return 0;
}
