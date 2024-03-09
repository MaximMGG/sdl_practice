#include <SDL2/SDL.h>
#include <iostream>
#include <cstdio>

#define ERROR(msg) fprintf(stderr, "FILE - %s, FUNC - %s, LINE - %d, MSG - %s\n", __FILE__, __FUNCTION__, __LINE__, msg)
constexpr int WIDTH {720};
constexpr int HEIGHT {480};
constexpr float GRAVITY {0.05f};



bool mouse_in_bounds(int& x, int &y) {
    return x > 0 && x < WIDTH - 20 && y > 0 && y < HEIGHT - 20;
}

bool mouse_in_rect(SDL_Rect& rect, int& x, int& y) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}


int main() {
    SDL_Window *win = nullptr;
    SDL_Renderer *rend = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        ERROR("SDL init do not work");
    } else {
        win = SDL_CreateWindow("Gravity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (win == NULL) {
            ERROR("Window is null");
        } else {
            rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
            if (rend == NULL) {
                ERROR("render is null");
                exit(1);
            }
        }
        SDL_Rect cube {.x = WIDTH / 2, .y = 20, .w = 20, .h = 20};

        bool run = true;
        bool fall = true;
        bool grap = false;
        SDL_Event e;
        int x, y;
        float cubey {float(cube.y)};

        while(run) {
            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    run = false;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    std::cout << "Mouse pressed\n";
                    if (mouse_in_rect(cube, e.motion.x, e.motion.y)) {
                        fall = false;
                        grap = true;
                    }
                }
                if (e.type == SDL_MOUSEBUTTONUP) {
                    std::cout << "mouse relised\n";
                    if (mouse_in_rect(cube, e.motion.x, e.motion.y)) {
                        fall = true;
                        grap = false;
                    }
                }
            }
            if (grap) {
                SDL_GetMouseState(&x, &y);
                if (mouse_in_bounds(x, y)) {
                    cube.x = x;
                    cube.y = y;
                    cubey = float(cube.y);
                }
            }

            if (fall) {
                if (cube.y < HEIGHT - cube.h) {
                    cubey += GRAVITY;
                    cube.y = int(cubey);
                }
            }

            SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(rend);

            SDL_SetRenderDrawColor(rend, 0xFF, 0x10, 0xAC, 0xFF);
            // SDL_RenderDrawRect(rend, &cube);
            SDL_RenderFillRect(rend, &cube);

            SDL_RenderPresent(rend);
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);


    return 0;
}
