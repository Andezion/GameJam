#ifndef GAMEJAM_MAN_H
#define GAMEJAM_MAN_H
#include <SDL2/SDL.h>

struct man_t
{
    SDL_Rect man;
    SDL_bool dead;
    int num;
    int is_home;
    SDL_Rect* base;
};

struct man_t spawn_man(SDL_Rect* base, int num);

SDL_Point find_path_man(struct man_t *mane);

int update_man(SDL_Rect castle, struct man_t *mane, int mousepressed);

void draw_man(SDL_Renderer *r, struct man_t *mane);


#endif //GAMEJAM_MAN_H
