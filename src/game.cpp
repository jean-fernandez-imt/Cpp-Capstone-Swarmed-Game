#include <iostream>

#include "game.h"

Game::Game(
  SDL_Renderer* renderer, 
  Aim* mark, 
  Player* spaceship,
  Gun* spaceshipGun,
  Army* enemyArmy)
    : _renderer(renderer),
      _mark(mark),
      _spaceship(spaceship),
      _spaceshipGun(spaceshipGun),
      _enemyArmy(enemyArmy) {}

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
    if( e->type == SDL_QUIT || _spaceship->getHP() <= 0) {
      *running = false;
    }
    //Handle inputs
    _mark->handleEvent(*e);
    _spaceship->handleEvent(*e);
    _spaceshipGun->handleEvent(*e);
    _enemyArmy->spawn();
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

  //Update the enemy Army
  _enemyArmy->move(timeStep);
  _enemyArmy->updateEnemies();

  //Update Collisions
  updateCollisions();

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
  _enemyArmy->render();

  //Update screen
  SDL_RenderPresent(_renderer);
}

int Game::getScore() {return _score;}

void Game::updateCollisions() {
  //Enemies vs Bullets
  auto enemies = _enemyArmy->getEnemies();
  auto bullets = _spaceshipGun->getBullets();

  for (auto enemy: enemies) {
    for (auto bullet: bullets) {
      if (checkCollision(enemy->getCollider(), bullet->getCollider())) {
        enemy->takeHit();
        bullet->takeHit();
      }
    }
  }

  //Enemies vs Player
  for (auto enemy: enemies) {
    if (checkCollision(enemy->getCollider(), _spaceship->getCollider())) {
      enemy->takeHit();
      _spaceship->takeHit();
    }
  }
}

bool Game::checkCollision(Collider& a, Collider& b) {
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared*totalRadiusSquared;

  //If the distance between the centers of the circles is less than the sum of their radii
  if(distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)){
      //The circles have collided
      return true;
  }

  //If not
  return false;
}

double Game::distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}