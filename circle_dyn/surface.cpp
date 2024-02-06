#include <SDL2/SDL.h>
#include <iostream>

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 800;

void set_pixel(SDL_Surface *sur, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    SDL_LockSurface(sur); 
    std::cout << "Left mouse was pressed (" << x << ", " << y << ")\n";
    uint8_t *pixels = (uint8_t *) sur->pixels;
    pixels[y * sur->pitch + x * sur->format->BytesPerPixel - 2] = r;
    pixels[y * sur->pitch + x * sur->format->BytesPerPixel - 1] = g;
    pixels[y * sur->pitch + x * sur->format->BytesPerPixel - 0] = b;
    SDL_UnlockSurface(sur); 
}

int main () {

    SDL_Window *win;
    SDL_Surface *win_sur;
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Surface", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    win_sur = SDL_GetWindowSurface(win);

    SDL_Event e;
    bool quit = false;
    while(!quit) {
        int x, y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x, &y);
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.button.button == SDL_BUTTON_LEFT) {
                set_pixel(win_sur, x, y, 255, 0, 0);
            }
        }
        SDL_UpdateWindowSurface(win);
    }

    SDL_FreeSurface(win_sur);
    SDL_DestroyWindow(win);

    SDL_Quit();
    return 0;
}
