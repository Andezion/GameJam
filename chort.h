#ifndef GAMEJAM_CHORT_H
#define GAMEJAM_CHORT_H
#include <SDL.h>

struct chort_t {
    SDL_Rect chort;
    SDL_bool dead;
    int num;
    int speed;
};

struct chort_t spawn_chort(SDL_Rect base);

int intersect(SDL_Rect r1, SDL_Rect r2);

int contains(SDL_Rect r, SDL_Point p);

SDL_Point find_path(SDL_Rect castle, struct chort_t * chort);

int update_chort(SDL_Rect castle, SDL_Renderer *renderer, struct chort_t  *chort, int mousepressed);

void draw_chort(SDL_Renderer *r, struct chort_t *chort);

int loadTextureArray(SDL_Renderer* renderer, const char** fileNames, int arraySize, SDL_Texture** textureArray);

#endif //GAMEJAM_CHORT_H
