#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#define true 1
#define false 0

#define WIDTH 1920
#define HEIGHT 1080


int main() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s", SDL_GetError());
    }
    SDL_Window *window = SDL_CreateWindow("Hello window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Surface *helloWorld = SDL_LoadBMP("green.bmp");
    
    SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
    SDL_UpdateWindowSurface(window);

    SDL_Event e;

    _Bool quit = false;

    while (!quit) {
        while (SDL_PollEvent( &e )) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
