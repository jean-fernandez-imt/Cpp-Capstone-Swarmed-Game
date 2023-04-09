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
#include "background.h"
#include "font.h"

//Controls the Game Mechanics
class Game {
  public:
    Game(
      Renderer* renderer, 
      Aim* mark, 
      Player* spaceship,
      Gun* spaceshipGun,
      Army* enemyArmy,
      Background* background,
      Font* testFont);
      
    void run();
    int getScore();

  private:
    Renderer* _renderer;
    Aim* _mark;
    Player* _spaceship;
    Gun* _spaceshipGun;
    Army* _enemyArmy;

    int _score{0};

    Timer _stepTimer;
    Timer _afterHitTimer;

    //Main Game Loop
    void input(SDL_Event* e, bool* running);
    void update(Timer* stepTimer);
    void render();

    //Collision control helper functions
    void updateCollisions();
    bool checkCollision(Collider& a, Collider& b);
    double distanceSquared(int x1, int y1, int x2, int y2);

    //Backgrounds
    Background* _background;
    Texture* _selectedBackground;

    Font* _testFont;
};

#endif