#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <random>

#include "renderer.h"
#include "aim.h"
#include "player.h"
#include "gun.h"
#include "army.h"
#include "timer.h"
#include "collider.h"

class Game {
  public:
    Game(
      SDL_Renderer* renderer, 
      Aim* mark, 
      Player* spaceship,
      Gun* spaceshipGun,
      Army* enemyArmy);
      
    void run();
    int getScore();

  private:
    SDL_Renderer* _renderer;
    Aim* _mark;
    Player* _spaceship;
    Gun* _spaceshipGun;
    Army* _enemyArmy;

    int _score{0};

    //Main Game Loop
    void input(SDL_Event* e, bool* running);
    void update(Timer* stepTimer);
    void render();

    //Collision control helper functions
    void updateCollisions();
    bool checkCollision(Collider& a, Collider& b);
    double distanceSquared(int x1, int y1, int x2, int y2);
};

#endif