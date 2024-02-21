#include <SDL2/SDL.h>

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {

    SDL_Window *win = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Draw ract", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect rect {100, 100, 600, 600};
    SDL_Surface *sur = SDL_LoadBMP("./sample.bmp");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(render, sur);
    SDL_FreeSurface(sur);


    bool run = true;
    SDL_Event e;

    while(run) {
        while(SDL_PollEvent(&e)) {
            

            if (e.type == SDL_QUIT) {
                run = false;
            }
        }

        SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(render);
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        // SDL_RenderDrawLine(render, 0, 5, WIDTH, 5);
        // SDL_RenderDrawLine(render, 0, 15, WIDTH, 15);
        int step = WIDTH / 20;

        SDL_RenderCopy(render, tex, NULL, &rect);

        for(int i = 0; i < WIDTH; i += step) {
            SDL_Rect r {i, 5, i + step, 15};
            SDL_RenderDrawRect(render, &r);
        }

        SDL_RenderPresent(render);
    }


    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}
