#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>


int HEIGHT = 800;
int WIDTH = 600;

void set_background(SDL_Renderer *renderer)
{
    /*int size = 25;
    SDL_Rect cell;
    cell.w = size;
    cell.h = size;

    for(int i = 0; i <= 32; i++)
    {
        for(int j = 0; j <= 24; j++)
        {
            cell.x = 800 + i * size;
            cell.y = 600 + j * size;
            
            int type = 1 + rand() % 6;
            if(i == 0 || j == 0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &cell);
            }
            else
            {
                if(type == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(type == 2)
                {
                    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(type == 3)
                {
                    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(type == 4)
                {
                    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(type == 5)
                {
                    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(type == 6)
                {
                    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }
    }*/
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
                switch(pick) {
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

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
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

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
