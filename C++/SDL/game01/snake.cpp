#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int GRID_SIZE = 20;
const int ROWS = WINDOW_HEIGHT / GRID_SIZE;
const int COLS = WINDOW_WIDTH / GRID_SIZE;

struct Point {
    int x, y;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

enum GameState { STATE_READY, STATE_RUNNING, STATE_PAUSED, STATE_OVER };

class SnakeGame {
public:
    SnakeGame() { reset(); }

    void reset() {
        dir = RIGHT;
        gameOver = false;
        grow = false;
        score = 0;
        snake.clear();
        snake.push_back({COLS / 2, ROWS / 2});
        snake.push_back({COLS / 2 - 1, ROWS / 2});
        snake.push_back({COLS / 2 - 2, ROWS / 2});
        placeFood();
    }

    void placeFood() {
        bool onSnake;
        do {
            onSnake = false;
            food.x = rand() % COLS;
            food.y = rand() % ROWS;
            for (auto &s : snake) {
                if (s.x == food.x && s.y == food.y) {
                    onSnake = true;
                    break;
                }
            }
        } while (onSnake);
    }

    void changeDirection(Direction newDir) {
        if ((dir == UP && newDir == DOWN) || (dir == DOWN && newDir == UP) ||
            (dir == LEFT && newDir == RIGHT) || (dir == RIGHT && newDir == LEFT))
            return;
        dir = newDir;
    }

    void update() {
        if (gameOver) return;
        Point head = snake.front();
        switch (dir) {
            case UP: head.y--; break;
            case DOWN: head.y++; break;
            case LEFT: head.x--; break;
            case RIGHT: head.x++; break;
        }
        // 穿墙处理
        if (head.x < 0) head.x = COLS - 1;
        if (head.x >= COLS) head.x = 0;
        if (head.y < 0) head.y = ROWS - 1;
        if (head.y >= ROWS) head.y = 0;
        // 撞自己
        for (auto &s : snake) {
            if (s.x == head.x && s.y == head.y) {
                gameOver = true;
                return;
            }
        }
        snake.push_front(head);
        if (head.x == food.x && head.y == food.y) {
            grow = true;
            placeFood();
            score++;
        }
        if (!grow) snake.pop_back();
        else grow = false;
    }

    void render(SDL_Renderer *renderer, GameState state, TTF_Font* font, SDL_Texture* bgTexture) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // 渲染背景图片
        if (bgTexture) {
            SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
        }
        SDL_Rect foodRect = {food.x * GRID_SIZE, food.y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &foodRect);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (auto &s : snake) {
            SDL_Rect r = {s.x * GRID_SIZE, s.y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
            SDL_RenderFillRect(renderer, &r);
        }
        // 状态提示（带文字）
        if (font) {
            std::string msg;
            SDL_Color color = {0, 0, 0, 255};
            if (state == STATE_READY) {
                msg = "按空格开始游戏";
                color = {0, 102, 255, 255};
            } else if (state == STATE_PAUSED) {
                msg = "已暂停，按空格继续";
                color = {128,64,0,255};
            } else if (state == STATE_OVER) {
                msg = "游戏结束，回车重新开始";
                color = {128,0,0,255};
            }
            if (state != STATE_RUNNING) {
                SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, msg.c_str(), color);
                if (textSurface) {
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    SDL_Rect textRect = {WINDOW_WIDTH/2 - textSurface->w/2, WINDOW_HEIGHT/2 - textSurface->h/2, textSurface->w, textSurface->h};
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                    SDL_FreeSurface(textSurface);
                    SDL_DestroyTexture(textTexture);
                }
            }
            // 显示分数
            std::stringstream ss;
            ss << "得分: " << score;
            SDL_Color scoreColor = {255, 255, 255, 255};
            SDL_Surface* scoreSurface = TTF_RenderUTF8_Blended(font, ss.str().c_str(), scoreColor);
            if (scoreSurface) {
                SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
                SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
                SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
                SDL_FreeSurface(scoreSurface);
                SDL_DestroyTexture(scoreTexture);
            }
        }
        SDL_RenderPresent(renderer);
    }

    bool isGameOver() const { return gameOver; }
    int getScore() const { return score; }

private:
    std::deque<Point> snake;
    Point food;
    Direction dir;
    bool gameOver;
    bool grow;
    int score;
};

int main(int argc, char *argv[]) {
    srand((unsigned int)time(nullptr));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *window = SDL_CreateWindow("贪吃蛇", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // 加载字体（请确保同目录下有simhei.ttf或更换为你自己的ttf字体）
    TTF_Font* font = TTF_OpenFont("simhei.ttf", 28);
    if (!font) font = TTF_OpenFont("C:/Windows/Fonts/simhei.ttf", 28);
    SnakeGame game;
    GameState state = STATE_READY;
    bool quit = false;
    Uint32 lastTick = SDL_GetTicks();
    const Uint32 interval = 100;
    SDL_Texture* bgTexture = IMG_LoadTexture(renderer, "bg.jpg");
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            if (e.type == SDL_KEYDOWN) {
                if (state == STATE_RUNNING) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                        case SDLK_w:
                            game.changeDirection(UP); break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            game.changeDirection(DOWN); break;
                        case SDLK_LEFT:
                        case SDLK_a:
                            game.changeDirection(LEFT); break;
                        case SDLK_RIGHT:
                        case SDLK_d:
                            game.changeDirection(RIGHT); break;
                        case SDLK_SPACE: state = STATE_PAUSED; break;
                        case SDLK_ESCAPE: quit = true; break;
                    }
                } else if (state == STATE_PAUSED) {
                    if (e.key.keysym.sym == SDLK_SPACE) state = STATE_RUNNING;
                    if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
                } else if (state == STATE_READY) {
                    if (e.key.keysym.sym == SDLK_SPACE) state = STATE_RUNNING;
                    if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
                } else if (state == STATE_OVER) {
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        game.reset();
                        state = STATE_READY;
                    }
                    if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
                }
            }
        }
        Uint32 now = SDL_GetTicks();
        if (state == STATE_RUNNING && now - lastTick > interval && !game.isGameOver()) {
            game.update();
            lastTick = now;
            if (game.isGameOver()) state = STATE_OVER;
        }
        game.render(renderer, state, font, bgTexture);
        SDL_Delay(10);
    }
    if (font) TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    if (bgTexture) SDL_DestroyTexture(bgTexture);
    IMG_Quit();
    return 0;
} 