//
// Created by ajeszny on 10.05.24.
//

#include "chort.h"

SDL_Rect spawn_chort(SDL_Rect base) {
    SDL_Rect chort = base;
    chort.h = 30;
    chort.w = 30;
    return chort;
}

int intersect(SDL_Rect r1, SDL_Rect r2) {
    return (
            !(r1.x > r2.x + r2.w || r2.x > r1.x + r1.w) &&
            !(r1.y > r2.y + r2.h || r2.y > r1.y + r1.h)
    );
}

SDL_Point find_path(SDL_Rect castle, SDL_Rect *chort) {
    SDL_Point res = {0, 0};
    int dir = rand() % 2;
    if (dir == 0) {
        int kierunek = castle.x - chort->x;
        if (kierunek < 0) {
            res.x = -1;
        } else {
            res.x = 1;
        }

    } else {
        int kierunek = castle.y - chort->y;
        if (kierunek < 0) {
            res.y = -1;
        } else {
            res.y = 1;
        }
    }
    return res;

}

int update_chort(SDL_Rect castle, SDL_Rect *chort) {
    if (intersect(castle, *chort)) {
        return 1;
    }
    SDL_Point kierunek = find_path(castle, chort);
    chort->x += kierunek.x * 10;
    chort->y += kierunek.y * 10;
    return 0;
}

void draw_chort(SDL_Renderer *r, SDL_Rect *chort) {
    SDL_SetRenderDrawColor(r, 255, 255, 0, 1);
    SDL_RenderFillRect(r, chort);
}