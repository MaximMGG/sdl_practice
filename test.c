#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#define true 1
#define false 0


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


_Bool init();

_Bool loadMedia();

void close();

SDL_Window *gWindow = NULL;

SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gHelloWorld = NULL;

int main() {
    //
    // if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    //     printf("SDL_Init Error: %s\n", SDL_GetError());
    //     return 1;
    // } 
    //
    // SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    // if (window == NULL) {
    //     printf("SDL_CreateWindow Error %s\n", SDL_GetError());
    //     return 1;
    // }
    //
    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // if (renderer == NULL) {
    //     printf("SDL_CreateRenderer Error %s\n", SDL_GetError());
    // }
    //
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);
    //
    // SDL_Delay(20000);
    //
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    //
    // SDL_Quit();
    //

    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            SDL_UpdateWindowSurface(gWindow);

            SDL_Event e;
            _Bool quit = false;

            while(quit == false)
                while(SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
        }
    }

    close();
    return 0;
}


_Bool init(void) {
    _Bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow(
                                    "SDL Tutur", 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SCREEN_WIDTH, 
                                    SCREEN_HEIGHT, 
                                    SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be create! SDL_Error %s\n", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

_Bool loadMedia() {
    _Bool success = true;

    gHelloWorld = SDL_LoadBMP("green.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL_Error: %s\n", "green.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close() {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

