//
// Created by ajeszny on 10.05.24.
//

#include "chort.h"

struct chort_t spawn_chort(SDL_Rect base) {
    struct chort_t chort;
    chort.chort = base;
    chort.chort.h = 30;
    chort.chort.w = 30;
    return chort;
}

int contains(SDL_Rect r, SDL_Point p) {
    return (
            r.x < p.x&&
            r.x + r.w > p.x&&
            r.y < p.y&&
            r.y + r.w > p.y
    );
}

int intersect(SDL_Rect r1, SDL_Rect r2) {
    return (
            !(r1.x > r2.x + r2.w || r2.x > r1.x + r1.w) &&
            !(r1.y > r2.y + r2.h || r2.y > r1.y + r1.h)
    );
}

SDL_Point find_path(SDL_Rect castle, struct chort_t  *chort) {
    SDL_Point res = {0, 0};
    int dir = rand() % 2;
    if (dir == 0) {
        int kierunek = castle.x - chort->chort.x;
        if (kierunek < 0) {
            res.x = -1;
        } else {
            res.x = 1;
        }

    } else {
        int kierunek = castle.y - chort->chort.y;
        if (kierunek < 0) {
            res.y = -1;
        } else {
            res.y = 1;
        }
    }
    return res;

}

int update_chort(SDL_Rect castle, struct chort_t  *chort) {
    
    if (intersect(castle, chort->chort)) {
        return 1;
    }
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if (contains(chort->chort, mouse)) {
        chort->chort.x = 99999;
    }
    SDL_Point kierunek = find_path(castle, chort);
    chort->chort.x += kierunek.x * 5;
    chort->chort.y += kierunek.y * 5;
    return 0;
}

void draw_chort(SDL_Renderer *r, struct chort_t *chort) {
    SDL_SetRenderDrawColor(r, 255, 255, 0, 1);
    SDL_RenderFillRect(r, chort);
}