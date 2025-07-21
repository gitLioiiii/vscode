#include <SDL2/SDL.h>
#include <iostream>
#undef main

const int WIDTH = 640;
const int HEIGHT = 480;

class Ball {
public:
    Ball(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), vx(1), vy(1) {}

    void move() {
        x += vx;
        y += vy;
        if (x <= 0 || x >= WIDTH - w) vx = -vx;
        if (y <= 0 || y >= HEIGHT - h) vy = -vy;
    }

    void draw(SDL_Renderer* renderer) {
        SDL_Rect rect = {x, y, w, h};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 设置绘制颜色为白色
        SDL_RenderFillRect(renderer, &rect);
    }

private:
    int x, y, w, h;
    int vx, vy;
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Ball Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Ball ball(WIDTH / 2, HEIGHT / 2, 20, 20);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 设置背景颜色为黑色
        SDL_RenderClear(renderer);

        ball.move();
        ball.draw(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(10); // 控制游戏循环速度
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}