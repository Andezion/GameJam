#include "chort.h"
#include <stdio.h>

SDL_Texture *texture_robot[4];

const char *robot[4] = {"../Sprites/robot1.bmp", "../Sprites/robot2.bmp", "../Sprites/robot1.bmp", "../Sprites/robot3.bmp"};
struct chort_t spawn_chort(SDL_Rect base)
{
    struct chort_t chort;
    chort.chort = base;

    int dupka = 30 + rand() % 10;
    chort.chort.h = dupka;
    chort.chort.w = dupka + 10;
    chort.num = 0;
    chort.dead = 0;
    chort.speed = 2 /*rand() % 2 + 1*/;
    return chort;
}

int contains(SDL_Rect r, SDL_Point p)
{
    return
    (
            r.x < p.x&&
            r.x + r.w > p.x&&
            r.y < p.y&&
            r.y + r.w > p.y
    );
}

int intersect(SDL_Rect r1, SDL_Rect r2)
{
    return
    (
            !(r1.x > r2.x + r2.w || r2.x > r1.x + r1.w) &&
            !(r1.y > r2.y + r2.h || r2.y > r1.y + r1.h)
    );
}

SDL_Point find_path(SDL_Rect castle, struct chort_t  *chort)
{
    SDL_Point res = {0, 0};
    int dir = rand() % 2;
    if (dir == 0)
    {
        int kierunek = castle.x - chort->chort.x;
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
        int kierunek = castle.y - chort->chort.y;
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

int loadTextureArray(SDL_Renderer* renderer, const char** fileNames, int arraySize, SDL_Texture** textureArray)
{
    for(int i = 0; i < arraySize; i++)
    {
        SDL_Surface* surface = SDL_LoadBMP(fileNames[i]);
        if (surface == NULL)
        {
            printf("Error loading image %d: %s\n", i, SDL_GetError());
            SDL_DestroyRenderer(renderer);
            return 1;
        }
        textureArray[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (textureArray[i] == NULL)
        {
            printf("Error creating texture for image %d: %s\n", i, SDL_GetError());
            SDL_DestroyRenderer(renderer);
            return 1;
        }
    }
    return 0;
}

int update_chort(SDL_Rect castle, struct chort_t  *chort, int mousepressed){
    if (chort->dead)
    {
        return 0;
    }
    if (intersect(castle, chort->chort))
    {
        return 1;
    }

    SDL_Point mouse;
    if (mousepressed) {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        if (contains(chort->chort, mouse)) {
            chort->dead = 1;
        }
    }
    SDL_Point kierunek = find_path(castle, chort);
    chort->chort.x += kierunek.x * chort->speed;
    chort->chort.y += kierunek.y * chort->speed;

    return 0;
}

void draw_chort(SDL_Renderer *r, struct chort_t *chort)
{
    if (chort->dead)
    {
        return;
    }
    loadTextureArray(r, robot, 4, texture_robot);
    SDL_RenderCopy(r, texture_robot[chort->num % 4], NULL, &chort->chort);
    for (int i = 0; i < 4; ++i) {
        SDL_DestroyTexture(texture_robot[i]);
    }
    chort->num = (chort->num + 1) % 4;

    for(int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(texture_robot[i]);
    }
}