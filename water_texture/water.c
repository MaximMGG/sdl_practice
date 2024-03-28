#include <SDL2/SDL.h>
#include <stdio.h>

#define serror(msg) fprintf(stderr, "%s - %s\n", msg, SDL_GetError());

#define WIDTH 640
#define HEIGHT 480


int main() {
    SDL_Window *win;
    SDL_Renderer *rend;

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        serror("SDL no init");
    } else {
        win = SDL_CreateWindow("Waterbland", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (win == NULL) {
            serror("win not create");
        } else {
            rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
            if (rend == NULL) {
                serror("Renderer not create");
            }

            SDL_Surface *sur = SDL_LoadBMP("./pool.bmp");
            // SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 0xFF, 0, 0xFF));

            SDL_Texture *tex1 = SDL_CreateTextureFromSurface(rend, sur);
            SDL_Texture *tex2 = SDL_CreateTextureFromSurface(rend, sur);

            SDL_FreeSurface(sur);


            SDL_Rect rect1 = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
            SDL_Rect rect2 = {.x = -639, .y = 0, .w = WIDTH, .h = HEIGHT};
            SDL_Rect rect3 = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
            SDL_Rect rect4 = {.x = 0, .y = -480, .w = WIDTH, .h = HEIGHT};


            SDL_Event e;
            int run = 1;

            while(run) {
                while(SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        run = 0;
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            SDL_SetTextureBlendMode(tex2, SDL_BLENDMODE_ADD);
                        } else if (e.button.button == SDL_BUTTON_MIDDLE) {
                            SDL_SetTextureBlendMode(tex2, SDL_BLENDMODE_BLEND);
                        } else if (e.button.button == SDL_BUTTON_RIGHT) {
                            SDL_SetTextureBlendMode(tex2, SDL_BLENDMODE_MOD);
                        }
                    }
                }
                SDL_SetRenderDrawColor(rend, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(rend);

                int w, h;
                SDL_QueryTexture(tex1, NULL, NULL, &w, &h);
                SDL_Delay(20);

                rect1.x++;
                if (rect1.x > 639) {
                    rect1.x = -639;
                }
                rect2.x++;
                if (rect2.x > 639) {
                    rect2.x = -639;
                }
                rect3.y++;
                if (rect3.y > 479) {
                    rect3.y = -480;
                }
                rect4.y++;
                if (rect4.y > 479) {
                    rect4.y = -480;
                }

                SDL_SetTextureBlendMode(tex1, SDL_BLENDMODE_NONE);
                SDL_RenderCopy(rend, tex1, NULL, &rect1);
                SDL_RenderCopy(rend, tex1, NULL, &rect2);

                SDL_RenderCopy(rend, tex2, NULL, &rect3);
                SDL_RenderCopy(rend, tex2, NULL, &rect4);


                SDL_RenderPresent(rend);
            }

        }

        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
    }




    return 0;
}
