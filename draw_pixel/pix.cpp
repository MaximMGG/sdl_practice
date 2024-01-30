#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480



int main() {

    SDL_Window *win = nullptr;
    SDL_Renderer *render = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &render);
    // SDL_RenderSetScale(render, 4, 4);

    SDL_SetRenderDrawColor(render, 0, 0, 0, 0xFF);
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawPoint(render, 640 / 2, 480 / 2);

    SDL_RenderPresent(render);

    SDL_Delay(10000);

    SDL_Quit();

    return 0;
}
