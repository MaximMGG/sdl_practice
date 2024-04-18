#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/m_list.h>


#define WIDTH 800
#define HEIGHT 600 
char table[HEIGHT][WIDTH];

struct point{
    int x;
    int y;
};

struct point *create_point(int x, int y) {
    struct point *new = (struct point *) malloc(sizeof(struct point));
    new->x = x;
    new->y = y;
    return new;
}

void do_gravity(List *l) {
    for(int i = 0; i < l->len; i++) {
        struct point *p = list_get(l, i);
        if (p->y) {
            p->y++;
        }
    }
}

void draw_send(SDL_Renderer *rend, List *l) {
    for(int i = 0; i < l->len; i++) {
        struct point *p = list_get(l, i);
        SDL_RenderDrawPoint(rend, p->x, p->y);
    }
}


int main() {

    SDL_Window *win;
    SDL_Renderer *rend;
    List *l = list_create(0, l_struct);

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("send", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    int run = 1;
    int mx, my;

    while(run) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = 0;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mx, &my);
                fprintf(stderr, "mouse x = %d, y = %d\n", mx, my);

                if (mx <= WIDTH && my <= HEIGHT) {
                    struct point *p = create_point(mx, my);
                    list_add(l, p);
                }
            }
        }

        SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
        do_gravity(l);
        draw_send(rend, l);

        SDL_RenderPresent(rend);

    }

    list_free_all(l);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    return 0;
}
