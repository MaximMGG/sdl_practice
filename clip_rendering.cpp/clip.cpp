#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <stdio.h>
#include <string>

const int WIDTH = 640;
const int HEIGHT = 480;

class LTexture {
    public:
        LTexture();
        ~LTexture();
        
        bool loadFromFile(std::string path);

        void free();

        void render(int x, int y, SDL_Rect *clip = NULL);

        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
};

bool init();

bool loadMedia();

void closed();

SDL_Window *gWindow = nullptr;

SDL_Renderer *gRenderer = nullptr;

SDL_Rect gSpriteClips[4];
LTexture gSpriteSheetTexture;


LTexture::LTexture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(std::string path) {
    free();

    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s SDL error %s\n", path.c_str(), SDL_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (newTexture == NULL) {
            printf("Create texture error %s\n", SDL_GetError());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y, SDL_Rect *clip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

bool init() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWindow = SDL_CreateWindow("SDL tut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {

    }
    return true;
}

bool loadMedia() {
    gSpriteSheetTexture.loadFromFile("dots.png");
    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 100;
    gSpriteClips[0].h = 100;

    gSpriteClips[1].x = 100;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 100;
    gSpriteClips[1].h = 100;

    gSpriteClips[2].x = 0;
    gSpriteClips[2].y = 100;
    gSpriteClips[2].w = 100;
    gSpriteClips[2].h = 100;

    gSpriteClips[3].x = 100;
    gSpriteClips[3].y = 100;
    gSpriteClips[3].w = 100;
    gSpriteClips[3].h = 100;
    return true;
}

void closed() {
    gSpriteSheetTexture.free();

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);

    IMG_Quit();
    SDL_Quit();
}


int main() {
    init();
    loadMedia();

    bool quit = false;
    SDL_Event e;


    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gSpriteSheetTexture.render(0, 0, &gSpriteClips[0]);

        gSpriteSheetTexture.render(WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);

        gSpriteSheetTexture.render(0, HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);
        gSpriteSheetTexture.render(WIDTH - gSpriteClips[3].w, HEIGHT - gSpriteClips[3].h, &gSpriteClips[3]);

        SDL_RenderPresent(gRenderer);
    }


    closed();
    return 0;
}


