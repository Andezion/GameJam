#include "man.h"
#include "chort.h"
#include <stdio.h>

SDL_Texture *texture_man[4];
const char *man[4] = {"../Sprites/man1.bmp", "../Sprites/man2.bmp", "../Sprites/man1.bmp", "../Sprites/man3.bmp"};

struct man_t spawn_man(SDL_Rect* base, int num)
{
    SDL_Rect* nextbase = (base + num + 1);
    if(num == 0)
    {
        nextbase = (base + 1);
    }
    if(num == 1)
    {
        nextbase = (base + 2);
    }
    if(num == 2)
    {
        nextbase = (base + 3);
    }
    if (num == 3)
    {
        nextbase = (base + 0);
    }


    struct man_t mane;
    mane.man = base[num];
    mane.man.h = 35;
    mane.man.w = 55;
    mane.num = 0;
    mane.dead = 0;
    mane.base = nextbase;
    return mane;
}

SDL_Point find_path_man(struct man_t *mane)
{
    SDL_Point res = {0, 0};
    int dir = rand() % 2;
    if (dir == 0)
    {
        int kierunek = mane->base->x - mane->man.x;
        if (kierunek < 0)
        {
            res.x = -1;
        }
        else
        {
            res.x = 1;
        }

    }
    else
    {
        int kierunek = mane->base->y - mane->man.y;
        if (kierunek < 0)
        {
            res.y = -1;
        }
        else
        {
            res.y = 1;
        }
    }
    return res;

}

int update_man(SDL_Rect castle, struct man_t *mane, int mousepressed)
{
    if(mane->dead)
    {
        return 0;
    }

    if(intersect(*mane->base, mane->man))
    {
        return 1;
    }

    SDL_Point mouse;
    if(mousepressed)
    {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        if(contains(mane->man, mouse))
        {
            mane->dead = 1;
        }
    }

    SDL_Point kierunek = find_path_man(mane);
    mane->man.x += kierunek.x * 2;
    mane->man.y += kierunek.y * 2;
    return 0;
}

void draw_man(SDL_Renderer *r, struct man_t *mane)
{
    if(mane->dead)
    {
        return;
    }
    loadTextureArray(r, man, 4, texture_man);
    SDL_RenderCopy(r,texture_man[mane->num % 4], NULL, &mane->man);
    mane->num = (mane->num + 1) % 4;

    for(int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(texture_man[i]);
    }
}
