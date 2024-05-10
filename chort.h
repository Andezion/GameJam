//
// Created by ajeszny on 10.05.24.
//

#ifndef GAMEJAM_CHORT_H
#define GAMEJAM_CHORT_H
#include <SDL.h>

struct chort_t {
    SDL_Rect chort;
    SDL_bool dead;
    int num;
};

struct chort_t spawn_chort(SDL_Rect base);

int intersect(SDL_Rect r1, SDL_Rect r2);

SDL_Point find_path(SDL_Rect castle, struct chort_t * chort);

int update_chort(SDL_Rect castle, struct chort_t * chort);

void draw_chort(SDL_Renderer* r, struct chort_t * chort);

int loadTextureArray(SDL_Renderer* renderer, const char** fileNames, int arraySize, SDL_Texture** textureArray);

#endif //GAMEJAM_CHORT_H
