#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>

constexpr int TEXTURE_W = 2000;
constexpr int TEXTURE_H = 2000;
constexpr int SCREEN_W = 1000;
constexpr int SCREEN_H = 1000;

int main() {

    SDL_Rect source{0, 0, SCREEN_W / 32, SCREEN_H / 32};
    SDL_Rect dest{10, 10, SCREEN_W - 20, SCREEN_H - 20};
    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Scrolling", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, 0);
    auto render = SDL_CreateRenderer(window, -1, 0);
    auto texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H);
    std::vector<SDL_Point> pv;
    for(int i = 0; i < 1000; i++) {
        pv.emplace_back(rand() % TEXTURE_H, rand() % TEXTURE_W);
    }
    auto running = true;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP: source.y -= 3; break;
                    case SDLK_DOWN: source.y += 3; break;
                    case SDLK_LEFT: source.x -= 3; break;
                    case SDLK_RIGHT: source.x += 3; break;
                    case SDLK_1: source.w *= 2; source.h *= 2; break;
                    case SDLK_2: source.w /= 2; source.h /= 2; break;
                }
            }
        }
        SDL_SetRenderTarget(render, texture);
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF,0xFF,0xFF);
        SDL_RenderClear(render);

        std::for_each(pv.begin(), pv.end(), [](auto& item) {
                item.x += rand() % 3 - 1;
                item.y += rand() % 3 - 1;
        });

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderDrawPoints(render, pv.data(), pv.size());


        SDL_SetRenderTarget(render, nullptr);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        SDL_RenderCopy(render, texture, &source, &dest);
        SDL_RenderPresent(render);

        SDL_Delay(50);
    }

    SDL_Quit();

    return 0;
}
