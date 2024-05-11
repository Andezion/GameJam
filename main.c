#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "chort.h"

// Константы
int HEIGHT = 800;
int WIDTH = 600;
int CURSORSIZE = 32;

int pick;

enum STATE {mainMenu, game, gameOver};

void loadTexture(SDL_Texture **Texture, SDL_Renderer *renderer, char* fileName) {
    SDL_Surface *Surface = IMG_Load(fileName);
    *Texture = SDL_CreateTextureFromSurface(renderer, Surface);
    int w = 32, h = 32;
    SDL_FreeSurface(Surface);
    //SDL_QueryTexture(cursorTexture, NULL, NULL, &w, &h);
}


// Рисует Курсор (пока белый квадрат)
void drawCoursor(SDL_Renderer *renderer, SDL_Texture *cursorTexture)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Rect cursor = {x-CURSORSIZE/2, y-CURSORSIZE/2, CURSORSIZE, CURSORSIZE};
    Uint8 r, g, b, a;
    // Запоминаем цвет
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
    //SDL_RenderFillRect(renderer, &cursor);
    SDL_RenderCopy(renderer, cursorTexture, NULL, &cursor);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

// Рисует задний фон
void set_background(SDL_Renderer *renderer, int pick)
{
    int cell_size = 20;

    SDL_Rect cell;
    cell.w = cell_size;
    cell.h = cell_size;


    for(int i = 0; i < 40; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            cell.x = i * cell_size;
            cell.y = j * cell_size;

            if(i == 0 || j == 0 || i == 39 || j == 29)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &cell);
            }
            else
            {
                switch(pick)
                {
                    case (1):
                        SDL_SetRenderDrawColor(renderer, 13, 28, 43, 255);
                        SDL_RenderFillRect(renderer, &cell);
                        break;
                    case (2):
                        SDL_SetRenderDrawColor(renderer, 43, 33, 3, 255);
                        SDL_RenderFillRect(renderer, &cell);
                        break;
                    case (3):
                        SDL_SetRenderDrawColor(renderer, 12, 25, 11, 255);
                        SDL_RenderFillRect(renderer, &cell);
                        break;
                    case (4):
                        SDL_SetRenderDrawColor(renderer, 11, 19, 25, 255);
                        SDL_RenderFillRect(renderer, &cell);
                        break;
                    case (5):
                        SDL_SetRenderDrawColor(renderer, 20, 16, 25, 255);
                        SDL_RenderFillRect(renderer, &cell);
                        break;
                    default:
                        SDL_SetRenderDrawColor(renderer, 25, 16, 20, 255);
                        SDL_RenderFillRect(renderer, &cell);
                        break;
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

// Рисует объекты (4 базы и крепость)
void drawMainObjects(SDL_Renderer *renderer)
{
    SDL_Surface* surface = SDL_LoadBMP("../Sprites/spawn.bmp");
    if (surface == NULL)
    {
        printf("Error loading image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL)
    {
        printf("Error creating texture for image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        return;
    }

    SDL_Rect base1 = {50, 50, 50, 50};
    SDL_RenderCopy(renderer, texture, 0, &base1);

    SDL_Rect base2 = {700, 50, 50, 50};
    SDL_RenderCopy(renderer, texture, 0, &base2);

    SDL_Rect base3 = {50, 500, 50, 50};
    SDL_RenderCopy(renderer, texture, 0, &base3);

    SDL_Rect base4 = {700, 500, 50, 50};
    SDL_RenderCopy(renderer, texture, 0, &base4);

    SDL_Surface *dupka = SDL_LoadBMP("../Sprites/dante.bmp");
    if (dupka == NULL)
    {
        printf("Error loading image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        return;
    }

    SDL_Texture *texturka = SDL_CreateTextureFromSurface(renderer, dupka);
    SDL_FreeSurface(dupka);
    if (texturka == NULL)
    {
        printf("Error creating texture for image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        return;
    }

    SDL_Rect main_fortress = {350, 250, 80, 80};
    SDL_RenderCopy(renderer, texturka, 0, &main_fortress);
}


void drawMainMenu(SDL_Renderer *renderer, SDL_Texture *logo, SDL_Texture *start, SDL_Texture *cat)
{
    SDL_Rect LogoPos = {200, 10, 480,32};
    SDL_RenderCopy(renderer, logo, NULL, &LogoPos);
    SDL_Rect StartPos = {160, 100, 480,32};
    SDL_RenderCopy(renderer, start, NULL, &StartPos);
    SDL_Rect CatPos = {160, 142, 480,480};
    SDL_RenderCopy(renderer, cat, NULL, &CatPos);
}

void drawGameOver(SDL_Renderer *renderer, SDL_Texture *gameOver)
{
    SDL_Rect overPos = {0, 0, 800,600};
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 40,40,40, 255);
    SDL_RenderFillRect(renderer, &overPos);
    SDL_RenderCopy(renderer, gameOver, NULL, &overPos);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    enum STATE state = mainMenu;
    SDL_ShowCursor(SDL_DISABLE);

    pick = 1 + rand() % 6;

    struct chort_t chort = spawn_chort((SDL_Rect){50, 500, 50, 50});
    SDL_Window *window = SDL_CreateWindow("Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        printf("Error in creating window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Error in creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);

        SDL_Quit();
        return 1;
    }

    // Загружаем Изображения
    SDL_Texture *cursorTexture = NULL;
    SDL_Texture *logo = NULL;
    SDL_Texture *start = NULL;
    SDL_Texture *cat = NULL;
    SDL_Texture *gameOverScreen = NULL;
    loadTexture(&cursorTexture, renderer, "../Sprites/Coursor.png");
    loadTexture(&logo, renderer, "../Sprites/Team Logo.png");
    loadTexture(&start, renderer, "../Sprites/StartGame.png");
    loadTexture(&cat, renderer, "../Sprites/cat.png");
    loadTexture(&gameOverScreen, renderer, "../Sprites/GameOver.png");


    SDL_Event event;

    int running = 1;
    while(running)
    {
        int mouse_pressed = 0;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_q)
            {
                running = 0;
            }
            if(event.type == SDL_MOUSEBUTTONUP && state == mainMenu)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > 160 && x < 640 && y > 100 && y < 132)
                {
                    state = game;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouse_pressed = 1;
            }
        }


        switch(state)
        {
            case mainMenu:
                //state = game;
                SDL_RenderClear(renderer);
                drawMainMenu(renderer, logo, start, cat);
                drawCoursor(renderer, cursorTexture);
                SDL_RenderPresent(renderer);
                break;
            case game:
                if (update_chort((SDL_Rect){350, 250, 80, 80}, &chort, mouse_pressed))
                    state = gameOver;
                SDL_RenderClear(renderer);
                // Тут начало отрисовки
                set_background(renderer, pick);
                drawMainObjects(renderer);
                drawCoursor(renderer, cursorTexture);
                draw_chort(renderer, &chort);
                // Тут конец отрисовки
                SDL_RenderPresent(renderer);
                break;
            case gameOver:
                SDL_RenderClear(renderer);
                drawGameOver(renderer, gameOverScreen);
                SDL_RenderPresent(renderer);
                SDL_Delay(2500);
                goto exit;
                exit(-1);
                break;
            default:
                exit(-5);
        }
    }
    exit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(cursorTexture);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(start);
    SDL_DestroyTexture(cat);
    IMG_Quit();
    SDL_Quit();

    return 0;
}