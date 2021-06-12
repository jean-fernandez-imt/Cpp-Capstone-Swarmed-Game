#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <random>

#include "renderer.h"
#include "aim.h"
#include "player.h"
#include "gun.h"
#include "timer.h"

class Game {
  public:
    Game(
      SDL_Renderer* renderer, 
      Aim* mark, 
      Player* spaceship,
      Gun* spaceshipGun);
      
    void run();
    int getScore();

  private:
    SDL_Renderer* _renderer;
    Aim* _mark;
    Player* _spaceship;
    Gun* _spaceshipGun;

    int _score{0};

    //Main Game Loop
    void input(SDL_Event* e, bool* running);
    void update(Timer* stepTimer);
    void render();
};

#endif