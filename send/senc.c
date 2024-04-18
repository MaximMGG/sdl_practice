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

void do_gravity(List *send) {
    for(int i = 0; i < send->len; i++) {
        struct point *temp = (struct point *)list_get(send, i);
        if (temp->x == HEIGHT - 1) {
            continue;
        } else {
            temp->y++;
            table[temp->x - 1][temp->y] = 0;
            table[temp->x][temp->y] = 1;
        }
    }
}

void draw_send(SDL_Window *win, SDL_Renderer *rend, List *send) {

    SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
    for(int i = 0; i < send->len; i++) {
        struct point *temp = (struct point *) list_get(send, i);
        SDL_RenderDrawPoint(rend, temp->x, temp->y);
    }
    SDL_RenderPresent(rend);
}


void free_list(List *l) {
    for(int i = 0; i < l->len; i++) {
        struct point *t = (struct point *)list_get(l, i);
        free(t);
    }

    list_free_all(l);
}


int main() {
    List *l = list_create(0, l_struct);

    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Send", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    int run = 1;
    int mx = 0;
    int my = 0;


    while(run) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = 0;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mx, &my);
                if (mx <= WIDTH && my <= HEIGHT) {
                    list_add(l, create_point(mx, my));
                }
            }
        }
        do_gravity(l);
        draw_send(win, rend, l);
        SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    return 0;
}
