#include <iostream>

#include "game.h"

Game::Game(
  SDL_Renderer* renderer, 
  Aim* mark, 
  Player* spaceship,
  Bullet* bullet)
    : _renderer(renderer),
      _mark(mark),
      _spaceship(spaceship),
      _bullet(bullet) {}

void Game::run() {
  Timer stepTimer;
  SDL_Event e;
  bool running = true;

  while (running) {
    //Main Game Loop
    input(&e, &running);
    update(&stepTimer);
    render();
  }
}

void Game::input(SDL_Event* e, bool* running) {
  //Handle events on queue
  while(SDL_PollEvent(e) != 0) {
    //User requests quit
    if( e->type == SDL_QUIT )
    {
      *running = false;
    }
    //Handle inputs
    _spaceship->handleEvent(*e);
    _mark->handleEvent(*e);
    _bullet->handleEvent(*e);
  }
}

void Game::update(Timer* stepTimer) {
  //Calculate time step
  float timeStep = stepTimer->getTicks() / static_cast<float>(1000);

  //Move the player
  _spaceship->move(timeStep);

  //Bullet fire
  _bullet->fire();

  //Restart step timer
  stepTimer->start();
}

void Game::render() {
  //Clear screen
  SDL_RenderClear(_renderer);

  //Render objects
  _spaceship->render();
  _mark->render();
  _bullet->render();

  //Update screen
  SDL_RenderPresent(_renderer);
}

int Game::getScore() {return _score;}