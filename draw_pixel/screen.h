#include <SDL2/SDL.h>
#include <vector>

#define WIDTH 640
#define HEIGHT 480

class Screen {
    
    SDL_Event e;
    SDL_Window *window;
    SDL_Renderer *render;
    std::vector<SDL_FPoint> points;
    public:

    Screen() {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &render);
        // SDL_RenderSetScale(render, 2, 2);
    }

    ~Screen() {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void pixel(float x, float y) {
        points.emplace_back(x, y);
    }

    void show() {
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        for(auto& point : points) {
            SDL_RenderDrawPointF(render, point.x, point.y);
        }
        SDL_RenderPresent(render);
    }

    void clear() {
        points.clear();
    }
    void input() {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
        }
    }
};
