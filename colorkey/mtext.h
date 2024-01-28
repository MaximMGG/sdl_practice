#ifndef _M_TEX_
#define _M_TEX_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "app.h"

typedef struct {
    SDL_Texture *mTex;
    int mWidth;
    int mHeight;
} LTexture;

LTexture *new_Tex();
void free_Tex(LTexture *tex);

boolean load_from_file(App *app, LTexture *tex, char *path);
void render(App *app, LTexture *tex, int x, int y);


#endif //_M_TEX_
