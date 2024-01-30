#include <SDL2/SDL.h>



#define WIDTH 1000
#define HEIGHT 1000

int main() {

    SDL_Init(SDL_INIT_EVERYTHING);

    auto win = SDL_CreateWindow("Texture",
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED,
                                WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    auto render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //Create texture
    auto red_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    auto blue_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);

    //red texture
    SDL_SetRenderTarget(render, red_texture);
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderClear(render);

    //blue texture
    SDL_SetRenderTarget(render, blue_texture);
    SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
    SDL_RenderClear(render);

    SDL_SetRenderTarget(render, nullptr);

    SDL_RenderCopy(render, red_texture, nullptr, nullptr);
    SDL_RenderPresent(render);
    SDL_Delay(10000);

    SDL_RenderCopy(render, blue_texture, nullptr, nullptr);
    SDL_RenderPresent(render);
    SDL_Delay(10000);

    SDL_Quit();

    return 0;
}
