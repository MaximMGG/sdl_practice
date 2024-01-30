#include <iostream>
#include <SDL2/SDL.h>
#include <pthread.h>

using namespace std;

#define WIDTH 1280
#define HEIGHT 720

bool mouse_in_rect(SDL_Rect rect, int x, int y) {
    return ((x >= rect.x && y >= rect.y) && (x < (rect.w + rect.x) && y < (rect.h + rect.y)));
}


int main() {
    
    SDL_Window *win = nullptr;
    SDL_Renderer *render = nullptr;
    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    bool run = true;
    SDL_Rect r{10, 10, 255, 255};
    SDL_Rect exit{WIDTH - 20, 20, 10, 10};
    int x, y;
    int tackts = 0;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &render);

    while(run) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        cout << "Right key was pressed\n";
                        r.x += 50;
                        break;
                }
            } else if(e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        cout << "Right key was released\n";
                        break;
                }
            } else if (e.type == SDL_MOUSEMOTION) {
                // SDL_GetMouseState(&r.x, &r.y);
                SDL_GetMouseState(&x, &y);
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&x, &y);
                cout << "Mouse button down" << endl;
                cout << "X: " << x << " Y: " << y << endl;
                if (mouse_in_rect(exit, x, y)) {
                    run = false;
                }

            }
        }

    
        if (mouse_in_rect(r, x, y)) {
            cout << "Coursore in rect" << tackts << " tackts\n";
            tackts++;
        } else {
            tackts = 0;
        }

        // cout << "Mouse x: " << x << " y: " << y << endl;

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderFillRect(render, &r);

        SDL_SetRenderDrawColor(render, 0xFF, 0, 0, 0xFF);
        SDL_RenderFillRect(render, &exit);

        SDL_RenderPresent(render);
        SDL_Delay(10);
    }

    return 0;
}
