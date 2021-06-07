#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <random>

#include "renderer.h"
#include "aim.h"
#include "player.h"
#include "bullet.h"
#include "timer.h"

class Game {
  public:
    Game(
      SDL_Renderer* renderer, 
      Aim* mark, 
      Player* spaceship,
      Bullet* bullet);
    void run();
    int getScore();

  private:
    SDL_Renderer* _renderer;
    Aim* _mark;
    Player* _spaceship;
    Bullet* _bullet;

    int _score{0};

    //Main Game Loop
    void input(SDL_Event* e, bool* running);
    void update(Timer* stepTimer);
    void render();
};

#endif