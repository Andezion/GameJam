#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Константы
int HEIGHT = 800;
int WIDTH = 600;
int CURSORSIZE = 32;

void drawCoursor(SDL_Renderer *renderer)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    Uint8 r, g, b, a;
    // Запоминаем цвет
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_Rect cursor = {x, y, CURSORSIZE, CURSORSIZE};
    SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
    SDL_RenderFillRect(renderer, &cursor);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

// Рисует задний фон
void set_background(SDL_Renderer *renderer)
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

            int pick = 1 + rand() % 6;

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

    SDL_Rect base1 = {50, 50, 50, 50};
    SDL_RenderFillRect(renderer, &base1);
    SDL_Rect base2 = {700, 50, 50, 50};
    SDL_RenderFillRect(renderer, &base2);
    SDL_Rect base3 = {50, 500, 50, 50};
    SDL_RenderFillRect(renderer, &base3);
    SDL_Rect base4 = {700, 500, 50, 50};
    SDL_RenderFillRect(renderer, &base4);

    SDL_Rect main_fortress = {350, 250, 80, 80};
    SDL_RenderFillRect(renderer, &main_fortress);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);
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

    SDL_Event event;

    int running = 1;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_q)
            {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        set_background(renderer);
        drawMainObjects(renderer);
        drawCoursor(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
