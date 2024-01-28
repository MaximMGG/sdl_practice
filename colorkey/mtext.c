#include "mtext.h"

LTexture *new_Tex() {
    LTexture *new = (LTexture *) malloc(sizeof(LTexture));
    new->mTex = NULL;
    new->mWidth = 0;
    new->mHeight = 0;

    return new;
}

void free_Tex(LTexture *tex) {
    if (tex->mTex != NULL) {
        SDL_DestroyTexture(tex->mTex);
        tex = NULL;
        tex->mWidth = 0;
        tex->mHeight = 0;
    }
}

boolean load_from_file(App *app, LTexture *tex, char *path) {
        free_Tex(tex);

        SDL_Texture *newTexture = NULL;

        SDL_Surface *loadedSurface = IMG_Load(path);

        if (loadedSurface == NULL) {
            IMG_ERR("Error load texture %s\n");
        } else {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

            newTexture = SDL_CreateTextureFromSurface(app->rend, loadedSurface);
            if (newTexture == NULL) {
                SDL_ERR("Load texture error %s\n");
            } else {
                tex->mHeight = loadedSurface->h;
                tex->mWidth = loadedSurface->w;
            }
        }

        SDL_FreeSurface(loadedSurface);

        tex->mTex = newTexture;
        return tex->mTex != NULL;
}

void render(App *app, LTexture *tex, int x, int y) {

    SDL_Rect renderQuad = {x, y, tex->mWidth, tex->mHeight};
    SDL_RenderCopy(app->rend, tex->mTex, NULL, &renderQuad);
}
