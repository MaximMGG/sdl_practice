#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <string>


const int S_WIDTH {640};
const int S_HEIGHT {480};

class Tex {
    private:
        SDL_Texture *mTex;
        int mWidth;
        int mHeight;

    public:
        Tex();
        ~Tex();

        bool loadFromFile(std::string path);
        void free();
        void setColor(Uint8 r, Uint8 g, Uint8 b);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 a);
        void render(int x, int y, SDL_Rect *clip = NULL);
        int getWidth();
        int getHeight();
};

SDL_Window *gWin;
SDL_Renderer *gRend;
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
Tex gSpriteSheetTexture;

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

    SDL_Surface *loadSur = IMG_Load(path.c_str());
    SDL_Texture *newTex {};

    SDL_SetColorKey(loadSur, SDL_TRUE, SDL_MapRGB(loadSur->format, 0, 0xFF, 0xFF));

    newTex = SDL_CreateTextureFromSurface(gRend, loadSur);

    mWidth = loadSur->w;
    mHeight = loadSur->h;

    SDL_FreeSurface(loadSur);

    mTex = newTex;
    return mTex != NULL;
}

void Tex::free(){ 
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

void Tex::setAlpha(Uint8 al) {
    SDL_SetTextureAlphaMod(mTex, al);
}

void Tex::render(int x, int y, SDL_Rect *clip) {
    SDL_Rect renderQ {x, y, mWidth, mHeight};

    if (clip != NULL) {
        renderQ.w = clip->w;
        renderQ.h = clip->h;
    }

    SDL_RenderCopy(gRend, mTex, clip, &renderQ);
}

int Tex::getWidth() {
    return mWidth;
}
int Tex::getHeight() {
    return mHeight;
}

bool init() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWin = SDL_CreateWindow("animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN);
    gRend = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(gRend, 0xFF, 0xFF, 0xFF, 0xFF);

    IMG_Init(IMG_INIT_PNG);
    return true;
}

bool loadMedia() {
    gSpriteSheetTexture.loadFromFile("foo.png");

    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 64;
    gSpriteClips[0].h = 205;

    gSpriteClips[1].x = 64;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 64;
    gSpriteClips[1].h = 205;

    gSpriteClips[2].x = 128;
    gSpriteClips[2].y = 0;
    gSpriteClips[2].w = 64;
    gSpriteClips[2].h = 205;

    gSpriteClips[3].x = 192;
    gSpriteClips[3].y = 0;
    gSpriteClips[3].w = 64;
    gSpriteClips[3].h = 205;


    return true;

}

void closed() {
    gSpriteSheetTexture.free();
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
    int frame = 0;

    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(gRend, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRend);

        SDL_Rect *currentClip = &gSpriteClips[frame / 4];
        gSpriteSheetTexture.render((S_WIDTH - currentClip->w) / 2, (S_HEIGHT - currentClip->h) / 2, currentClip);

        SDL_Delay(30);
        SDL_RenderPresent(gRend);

        ++frame;

        if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
            frame = 0;
        }
    }
    closed();

    return 0;
}

