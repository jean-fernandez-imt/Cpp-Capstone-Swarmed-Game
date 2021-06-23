#include <iostream>

#include "parameters.h"
#include "game.h"

Game::Game(
  Renderer* renderer, 
  Aim* mark, 
  Player* spaceship,
  Gun* spaceshipGun,
  Army* enemyArmy,
  Background* background)
    : _renderer(renderer),
      _mark(mark),
      _spaceship(spaceship),
      _spaceshipGun(spaceshipGun),
      _enemyArmy(enemyArmy),
      _background(background) {
        //Select random Background
        _selectedBackground = _background->getRandomBackgound();

        //Start invulnerability Timer
        _afterHitTimer.start();
      }

void Game::run() {
  SDL_Event e;
  bool running = true;

  while (running) {
    //Main Game Loop
    input(&e, &running);
    update(&_stepTimer);
    render();
  }
}

void Game::input(SDL_Event* e, bool* running) {
  //Handle events on queue
  while(SDL_PollEvent(e) != 0) {
    //User requests "Quit" or out of HP
    if( e->type == SDL_QUIT || _spaceship->getHP() <= 0) {
      *running = false;
    }
    //Handle inputs
    _mark->handleEvent(*e);
    _spaceship->handleEvent(*e);
    _spaceshipGun->handleEvent(*e);
  }

  _enemyArmy->spawn();
}

void Game::update(Timer* stepTimer) {
  //Calculate time step (currently using VSync)
  float timeStep = stepTimer->getTicks() / static_cast<float>(1000);

  //Player's motion control
  _spaceship->move(timeStep);
  _spaceship->updateAngle(_mark->getPosition());

  //Update the Gun's position and state
  _spaceshipGun->updateGun();

  //Update the enemy Army
  _enemyArmy->move(timeStep);
  _enemyArmy->updateEnemies();

  updateCollisions();

  _renderer->UpdateWindowTitle(_score, _spaceship->getHP());

  stepTimer->start();
}

void Game::render() {
  SDL_RenderClear(_renderer->getRenderer());

  //Render Background
  _selectedBackground->render(0, 0);

  //Render objects
  _mark->render();
  _spaceship->render();
  _spaceshipGun->render();
  _enemyArmy->render();

  SDL_RenderPresent(_renderer->getRenderer());
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
        _score += 1;
      }
    }
  }

  //Enemies vs Player
  for (auto enemy: enemies) {
    if (checkCollision(enemy->getCollider(), _spaceship->getCollider())) {
      if (_afterHitTimer.getTicks() >= GAME_INVINCIBILITY_TIME) {
        _afterHitTimer.start();
        enemy->takeHit();
        _spaceship->takeHit();
      }
    }
  }
}

bool Game::checkCollision(Collider& a, Collider& b) {
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared*totalRadiusSquared;

  /* Collision: If the distance between the centers of 
  the circles is less than the sum of their radii */
  if(distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)){
      //The circles have collided
      return true;
  }

  return false;
}

double Game::distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}