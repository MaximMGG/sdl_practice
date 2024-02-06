#include <SDL2/SDL.h>
#include <cmath>

#define WIDTH 1000
#define HEIGHT 800
#define START_X 500
#define START_Y 400
#define RADIAN(x) x * PI/180

constexpr uint8_t R = 255;
constexpr uint8_t G = 0;
constexpr uint8_t B = 0;
const double PI = 3.14159265358979323846;
const double GOLDEN_RATION = (1 + std::sqrt(5)) / 2;
double RAD = 200;


int main() {
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Surface *sur;
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    sur = SDL_GetWindowSurface(win);

    // SDL_UpdateWindowSurface(win);

    int quit = 1;
    SDL_Event e;
    float first_circle_i = 0.0;
    float second_circle_i = 0.0;
    float first_x;
    float first_y;
    float c_x;
    float c_y;
    float fci_iterator = 0.2;
    double angleIncrement = 2 * PI / GOLDEN_RATION;

    while(quit) {
        while(SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_q) {
                quit = 0;
            }
        }

        c_x = cos(RADIAN(first_circle_i));
        c_y = sin(RADIAN(first_circle_i));
        first_circle_i += fci_iterator;
        // if (first_circle_i >= 360.0) {
        //     first_circle_i = 0.0;
        // }

        first_x = START_X + RAD * c_x;
        first_y = START_Y + RAD * c_y;

        for(int i = 0; i < 3; i++) {
            float angle = second_circle_i * angleIncrement;
            c_x = cos(RADIAN(angle));
            c_y = sin(RADIAN(angle));
            int xx = first_x + RAD * c_x;
            int yy = first_y + RAD * c_y;
            second_circle_i += 0.1;
            // if (second_circle_i >= 360.0) second_circle_i = 0.0;

            SDL_LockSurface(sur);
            uint8_t *buf = (uint8_t *) sur->pixels;
            buf[yy * sur->pitch + xx * sur->format->BytesPerPixel - 2] = R;
            buf[yy * sur->pitch + xx * sur->format->BytesPerPixel - 1] = G;
            buf[yy * sur->pitch + xx * sur->format->BytesPerPixel] = B;
            SDL_UnlockSurface(sur);
            SDL_Delay(3);
            SDL_UpdateWindowSurface(win);
        }
    }

    SDL_FreeSurface(sur);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
