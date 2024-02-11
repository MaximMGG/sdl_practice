#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string>

const int S_WIDTH = 640;
const int S_HEIGHT = 480;


class LTexture {
    public:
        LTexture();
        ~LTexture();

        bool loadFromFile(std::string path);
        void free();
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void render(int x, int y, SDL_Rect *clip = nullptr);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture *mTexture;

        int mWidth;
        int mHeight;
};

bool init();
bool loadMedia();
void closed();
SDL_Window *win = nullptr;
SDL_Renderer *rend = nullptr;

LTexture gModulatedTexture;

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

    SDL_Texture *newTexture {};
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! sdl error %s\n", path.c_str(), SDL_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);

        if (newTexture == NULL) {
            printf("Unable to create texture from surase %s sdl error %s\n", path.c_str(), SDL_GetError());
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
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::render(int x, int y, SDL_Rect *clip) {
    SDL_Rect renderQuad {x, y, mWidth, mHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(rend, mTexture, clip, &renderQuad);
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
    win = SDL_CreateWindow("Color modulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
    IMG_Init(IMG_INIT_PNG);

    return true;
}

bool loadMedia() {
    gModulatedTexture.loadFromFile("colors.png");
    return true;
}

void closed() {
    gModulatedTexture.free();

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();
}

int main() {

    init();
    loadMedia();

    bool quit = false;
    SDL_Event e;

    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;

    while(!quit) {
        while (SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_q:
                        r += 32;
                        break;
                    case SDLK_w:
                        g +=32;
                    case SDLK_e:
                        b += 32;
                        break;
                    case SDLK_a:
                        r -= 32;
                        break;
                    case SDLK_s:
                        g -= 32;
                        break;
                    case SDLK_d:
                        b -= 32;
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(rend);

        gModulatedTexture.setColor(r, g, b);
        gModulatedTexture.render(0, 0);

        SDL_RenderPresent(rend);
    }

    closed();

    return 0;
}




