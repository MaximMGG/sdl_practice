#include <SDL2/SDL.h>
#include <cmath>

#define RAD 200 
#define WIDTH 1000
#define HEIGHT 800
#define START_X 500
#define START_Y 400
#define PI 3.14
#define RADIAN(x) x * PI/180


void draw_circle(SDL_Renderer *rend, SDL_Texture *black) {
    for(float i = 0.00; i < 360.0; i+=0.02) {
        float x = cos(RADIAN(i));
        float y = sin(RADIAN(i));
        SDL_RenderDrawPointF(rend, START_X + RAD * x, START_Y + RAD * y);
        SDL_RenderPresent(rend);
        SDL_Delay(50);
        SDL_RenderClear(rend);
    }
}


int main() {
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *black = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);

    
    SDL_SetRenderTarget(rend, black);
    SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(rend);
    SDL_SetRenderTarget(rend, nullptr);


    draw_circle(rend, black);
    SDL_RenderPresent(rend);

    int quit = 1;
    SDL_Event e;
    while(quit) {
        while(SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_q) {
                quit = 0;
            }
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
