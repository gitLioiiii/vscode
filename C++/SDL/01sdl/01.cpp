#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#undef main

int main( int argc , char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Delay(3000); // 3 seconds
    SDL_DestroyWindow(window);
    SDL_Quit();
    system("pause");
    SDL_Log("hello world!");
    return 0;
}