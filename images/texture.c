#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    SDL_Texture *texture;
    SDL_Window *win;
    SDL_Renderer *rend;
} App;


void init(App *app) { 
    app->win = SDL_CreateWindow("Image window", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);

    app->rend = 

    

}


SDL_Texture *load_texture(char *path) {

    return NULL;
}



int main() {
    return 0;
}
