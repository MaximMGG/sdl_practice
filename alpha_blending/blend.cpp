#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


#define PRINT_ERR std::cout << __LINE__ << " error " << SDL_GetError() << std::endl;     
const int S_WIDTH {640};
const int S_HEIGHT {480};


class Tex {
    public:
        Tex();
        ~Tex();

        bool loadFromFile(std::string path);
        void free();
        void setColor(Uint8 r, Uint8 g, Uint8 b);
        void setBlendMode(SDL_BlendMode blenging);
        void setAlpha(Uint8 alpha);
        void render(int x, int y, SDL_Rect *clip = NULL);

        int getWidth();
        int getHeight();
    private:
        SDL_Texture *mTex;
        int mWidth;
        int mHeight;
};

SDL_Window *gWin;
SDL_Renderer *gRend;
Tex gModulatedTexture;
Tex gBackgroundTexture;

Tex::Tex() {
    mTex = NULL;
    mWidth = 0;
    mHeight = 0;
}

Tex::~Tex() {
    free();
}

bool Tex::loadFromFile(std::string path) {
    free();
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadSur = IMG_Load(path.c_str());

    if (loadSur == NULL) {PRINT_ERR;}
    else {
        SDL_SetColorKey(loadSur, SDL_TRUE, SDL_MapRGB(loadSur->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(gRend, loadSur);
        if (newTexture == NULL) {PRINT_ERR;}
        else {
            mWidth = loadSur->w;
            mHeight = loadSur->h;
        }
        SDL_FreeSurface(loadSur);
    }
    mTex = newTexture;
    return mTex != NULL;
}

void Tex::free() {
    if (mTex != NULL) {
        SDL_DestroyTexture(mTex);
        mTex = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void Tex::setColor(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetTextureColorMod(mTex, r, g, b);
}

void Tex::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTex, blending);
}

void Tex::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTex, alpha);
}

void Tex::render(int x, int y, SDL_Rect *clip) {
    SDL_Rect renderQuad {x, y, mWidth, mHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.y = clip->y;
    }

    SDL_RenderCopy(gRend, mTex, clip, &renderQuad);
}

int Tex::getWidth() {
    return mWidth;
}
int Tex::getHeight() {
    return mHeight;
}

bool init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    gWin = SDL_CreateWindow("Blending test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN);
    gRend = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRend, 0xFF, 0xFF, 0xFF, 0xFF);

    IMG_Init(IMG_INIT_PNG);

    return true;
}

bool loadMedia() {
    gModulatedTexture.loadFromFile("fadeout.png");
    gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    gBackgroundTexture.loadFromFile("fadein.png");

    return true;
}

void closed() {
    gModulatedTexture.free();
    gBackgroundTexture.free();

    SDL_DestroyRenderer(gRend);
    SDL_DestroyWindow(gWin);

    IMG_Quit();
    SDL_Quit();
}

int main() {

    init();
    loadMedia();


    bool quit = false;
    SDL_Event e;
    Uint8 a = 255;
    bool up = false;

    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_w) {
                    if (a + 32 > 255) {
                        a = 255;
                    } else {
                        a += 32;
                    }
                } else if (e.key.keysym.sym == SDLK_s) {
                    if (a - 32 < 0) {
                        a = 0;
                    } else {
                        a -= 32;
                    }
                }
            }

        }
        SDL_SetRenderDrawColor(gRend, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRend);
        if (up) {
            a++;
        } else {
            a--;
        }

        if (a >= 255) {up = false;}
        else if (a <= 0) {up = true;}

        gBackgroundTexture.render(0, 0);
        gModulatedTexture.setAlpha(a);
        gModulatedTexture.render(0, 0);
        SDL_Delay(15);

        SDL_RenderPresent(gRend);
    }

    closed();
    return 0;
}

