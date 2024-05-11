cmake_minimum_required(VERSION 3.23)
project(GameJam C)

set(CMAKE_C_STANDARD 11)
set(SDL2_INCLUDE_DIR C:\\Libs\\SDL\\include)
set(SDL2_LIB_DIR C:\\Libs\\SDL\\lib)
set(SDL2_IMAGE_INCLUDE_DIR C:\\Libs\\SDL_image\\include)
set(SDL2_IMAGE_LIB_DIR C:\\Libs\\SDL_image\\lib)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${SDL2_IMAGE_LIB_DIR})

add_executable(GameJam main.c
        chort.c
        chort.h man.c man.h)

target_link_libraries(GameJam SDL2main SDL2 SDL2_image SDL2_ttf)

