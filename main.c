#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "chort.h"
#include "man.h"

// Константы
int HEIGHT = 800;
int WIDTH = 600;
int CURSORSIZE = 32;
int MAXCHORTAMOUNT = 32;

unsigned long long timeStart;
unsigned long long timeFromSpawn;

int ochko_andreja = 0;

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
void set_background(SDL_Renderer *renderer, int pick[40][30])
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
                if(pick[i][j] == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 13, 28, 43, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(pick[i][j] == 2)
                {
                    SDL_SetRenderDrawColor(renderer, 43, 33, 3, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(pick[i][j] == 3)
                {
                    SDL_SetRenderDrawColor(renderer, 12, 25, 11, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(pick[i][j] == 4)
                {
                    SDL_SetRenderDrawColor(renderer, 11, 19, 25, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(pick[i][j] == 5)
                {
                    SDL_SetRenderDrawColor(renderer, 20, 16, 25, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                if(pick[i][j] == 6)
                {
                    SDL_SetRenderDrawColor(renderer, 25, 16, 20, 255);
                    SDL_RenderFillRect(renderer, &cell);
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
    SDL_DestroyTexture(texture);

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
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texturka);

    TTF_Font* f;
    f = TTF_OpenFont("../Sprites/font.ttf", 100);
    if (!f) {
        printf("%s", TTF_GetError());
        exit(-1);

    }
    char num[255] = {0};
    sprintf(num, "%4i", ochko_andreja);
    SDL_Surface* pointsurface = TTF_RenderText_Solid(f, num, (SDL_Color) {255, 255, 255, 0});
    SDL_Texture* txt = SDL_CreateTextureFromSurface(renderer, pointsurface);
    SDL_Rect r = {700, 0, 100, 50};
    SDL_RenderCopy(renderer, txt, 0, &r);
    TTF_CloseFont(f);
    SDL_FreeSurface(pointsurface);
    SDL_DestroyTexture(txt);
}

int current_hit_up = 0;
int current_hit_up1 = 0;

void drawMainMenu(SDL_Renderer *renderer, SDL_Texture *logo, SDL_Texture *start)
{
    SDL_Texture *texture_for_standing_in_plus[4];
    const char *standing_files_in_plus[4] = {"../Sprites/bot_down1.bmp", "../Sprites/bot_down2.bmp", "../Sprites/bot_down1.bmp", "../Sprites/bot_down2.bmp"};
    if(loadTextureArray(renderer, standing_files_in_plus, 4, texture_for_standing_in_plus) != 0)
    {
        return;
    }
    SDL_Rect hut = {300, 400, 150, 150};
    SDL_RenderCopy(renderer, texture_for_standing_in_plus[current_hit_up % 4], NULL, &hut);
    current_hit_up = (current_hit_up + 1) % 4;

    SDL_Texture *texture_for[4];
    const char *standing_files[4] = {"../Sprites/stand1.bmp", "../Sprites/stand2.bmp", "../Sprites/stand2.bmp", "../Sprites/stand1.bmp"};
    if(loadTextureArray(renderer, standing_files, 4, texture_for) != 0)
    {
        return;
    }
    SDL_Rect hut1 = {100, 400, 170, 150};
    SDL_RenderCopy(renderer, texture_for[current_hit_up1 % 4], NULL, &hut1);
    current_hit_up1 = (current_hit_up1 + 1) % 4;

    SDL_Delay(100);

    SDL_Rect LogoPos = {200, 10, 480, 32};
    SDL_RenderCopy(renderer, logo, NULL, &LogoPos);
    SDL_Rect StartPos = {160, 100, 480,32};
    SDL_RenderCopy(renderer, start, NULL, &StartPos);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
}

void drawGameOver(SDL_Renderer *renderer, SDL_Texture *gameOver, SDL_Texture *restartScreen)
{
    SDL_Rect overPos = {100, 0, 560,420};
    SDL_Rect restartPos = {280, 400, 240, 180};
    SDL_Rect screen = {0, 0, 800, 600};
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 40,40,40, 255);
    SDL_RenderFillRect(renderer, &screen);
    SDL_RenderCopy(renderer, gameOver, NULL, &overPos);
    SDL_RenderCopy(renderer, restartScreen, NULL, &restartPos);


    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int main(int argc, char *argv[])
{
    do {
        SDL_Rect bases[] = {{50,  50,  50, 50},
                            {700, 50,  50, 50},
                            {50,  500, 50, 50},
                            {700, 500, 50, 50}};
        SDL_Init(SDL_INIT_EVERYTHING);
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        int restartFlag = 0;
        enum STATE state = mainMenu;
        SDL_ShowCursor(SDL_DISABLE);
        Mix_Music* pem = Mix_LoadMUS("../Sprites/test.mp3");
        Mix_Music* main_game = Mix_LoadMUS("../Sprites/pduch.mp3");
        Mix_Music* end_game = Mix_LoadMUS("../Sprites/end.mp3");

        int pick[40][30];
        for (int i = 0; i < 40; i++) {
            for (int j = 0; j < 30; j++) {
                int num = 1 + rand() % 6;
                pick[i][j] = num;
            }
        }

        struct chort_t cherti[10] = {0};
        struct man_t mane[10] = {0};
        int man_num = 4;
        int cherti_num = 4;
        int chortAmount;
        SDL_Window *window = SDL_CreateWindow("GameJam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH,
                                              SDL_WINDOW_OPENGL);
        if (window == NULL) {
            printf("Error in creating window: %s\n", SDL_GetError());
            return 1;
        }
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            printf("Error in creating renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);

            SDL_Quit();
            return 1;
        }

        for (int i = 0; i < cherti_num; ++i) {
            cherti[i] = spawn_chort(bases[rand() % 4]);
        }

        for (int i = 0; i < man_num; i++) {
            mane[i] = spawn_man(bases, rand() % 4);
        }

        // Загружаем Изображения
        SDL_Texture *cursorTexture = NULL;
        SDL_Texture *logo = NULL;
        SDL_Texture *start = NULL;
        SDL_Texture *gameOverScreen = NULL;
        SDL_Texture *restarScreen = NULL;
        loadTexture(&cursorTexture, renderer, "../Sprites/Coursor.png");
        loadTexture(&logo, renderer, "../Sprites/Team Logo.png");
        loadTexture(&start, renderer, "../Sprites/StartGame.png");
        loadTexture(&gameOverScreen, renderer, "../Sprites/GameOver.png");
        loadTexture(&restarScreen, renderer, "../Sprites/PressRToRestart.png");


        SDL_Event event;

        int running = 1;

            while (running) {
                for (int i = 0; i < cherti_num; ++i) {
                    if (cherti[i].dead && ((rand() % 100) == 0)) {
                        ochko_andreja += cherti[i].speed * 5;
                        cherti[i] = spawn_chort(bases[rand() % 4]);
                    }
                }

                for (int i = 0; i < man_num; i++) {
                    if (mane[i].dead && ((rand() % 100) == 0)) {
                        ochko_andreja -= 2 * 5;
                        mane[i] = spawn_man(bases, rand() & 4);
                    }
                    if (mane[i].is_home && ((rand() % 100) == 0)) {
                        ochko_andreja += 5;
                        mane[i] = spawn_man(bases, rand() & 4);
                    }
                }
                int mouse_pressed = 0;
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        running = 0;
                    }
                    if (event.type == SDL_MOUSEBUTTONUP && state == mainMenu) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        if (x > 160 && x < 640 && y > 100 && y < 132) {
                            Mix_PlayMusic(main_game, -1);
                            state = game;
                            timeStart = SDL_GetTicks();
                        }
                    }
                    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r && state == gameOver) {
                        goto exit;
                    }

                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        mouse_pressed = 1;
                    }

                }

                // Ебля со временем
                unsigned long long currentTime = SDL_GetTicks();
                if (currentTime - timeFromSpawn > 2500) {

                }


                switch (state)
                {
                    case mainMenu:
                        //state = game;
                        SDL_RenderClear(renderer);
                        drawMainMenu(renderer, logo, start);
                        drawCoursor(renderer, cursorTexture);
                        SDL_RenderPresent(renderer);
                        if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic(pem, -1);
                        break;
                    case game:
                        for (int i = 0; i < cherti_num; ++i)
                        {
                            if (update_chort((SDL_Rect) {350, 250, 80, 80}, renderer, cherti + i, mouse_pressed))
                            {
                                Mix_PlayMusic(end_game, -1);
                                state = gameOver;
                            }
                        }
                        for (int i = 0; i < man_num; ++i)
                        {
                            if (update_man((SDL_Rect) {350, 250, 80, 80}, mane + i, mouse_pressed))
                            {
                                //mane[i].dead = 1;
                            }
                        }

                        SDL_RenderClear(renderer);
                        // Тут начало отрисовки
                        set_background(renderer, pick);
                        drawMainObjects(renderer);
                        for (int i = 0; i < cherti_num; ++i) {
                            draw_chort(renderer, cherti + i);
                        }
                        for (int i = 0; i < man_num; i++) {
                            draw_man(renderer, mane + i);
                        }
                        drawCoursor(renderer, cursorTexture);
                        // Тут конец отрисовки
                        SDL_RenderPresent(renderer);
                        if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic(main_game, -1);
                        break;
                    case gameOver:
                        SDL_RenderClear(renderer);
                        drawGameOver(renderer, gameOverScreen, restarScreen);
                        SDL_RenderPresent(renderer);
                        if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic(end_game, -1);
                        break;
                    default:
                        return 5;
                }
            }

            exit:
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_DestroyTexture(cursorTexture);
            SDL_DestroyTexture(logo);
            SDL_DestroyTexture(start);
            SDL_DestroyTexture(gameOverScreen);
            SDL_DestroyTexture(restarScreen);
            Mix_PlayMusic(pem, -1);
            if (!running)
                return 0;

    }while(1);
}