#include <iostream>

#include "game.h"

Game::Game(
  SDL_Renderer* renderer, 
  Aim* mark, 
  Player* spaceship,
  Gun* spaceshipGun)
    : _renderer(renderer),
      _mark(mark),
      _spaceship(spaceship),
      _spaceshipGun(spaceshipGun) {}

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
    _mark->handleEvent(*e);
    _spaceship->handleEvent(*e);
    _spaceshipGun->handleEvent(*e);
  }
}

void Game::update(Timer* stepTimer) {
  //Calculate time step
  float timeStep = stepTimer->getTicks() / static_cast<float>(1000);

  //Move the player
  _spaceship->move(timeStep);

  //Rotate the player
  _spaceship->updateAngle(_mark->getPosition());

  //Update the Gun's position and state
  _spaceshipGun->updateGun();

  //Restart step timer
  stepTimer->start();
}

void Game::render() {
  //Clear screen
  SDL_RenderClear(_renderer);

  //Render objects
  _mark->render();
  _spaceship->render();
  _spaceshipGun->render();

  //Update screen
  SDL_RenderPresent(_renderer);
}

int Game::getScore() {return _score;}