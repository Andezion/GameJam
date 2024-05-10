//
// Created by ajeszny on 10.05.24.
//

#ifndef GAMEJAM_CHORT_H
#define GAMEJAM_CHORT_H
#include <SDL2/SDL.h>

SDL_Rect spawn_chort(SDL_Rect base);

int intersect(SDL_Rect r1, SDL_Rect r2);

SDL_Point find_path(SDL_Rect castle, SDL_Rect* chort);

int update_chort(SDL_Rect castle, SDL_Rect* chort);

void draw_chort(SDL_Renderer* r, SDL_Rect* chort);

#endif //GAMEJAM_CHORT_H
