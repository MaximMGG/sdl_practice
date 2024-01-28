#ifndef _APP_
#define _APP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SDL_ERR(a) fprintf(stderr, a, SDL_GetError())
#define IMG_ERR(a) fprintf(stderr, a, IMG_GetError())

typedef int boolean;
#define true 1
#define false 0

typedef struct {
    SDL_Window *win;
    SDL_Renderer *rend;
} App;


#endif //_APP_

