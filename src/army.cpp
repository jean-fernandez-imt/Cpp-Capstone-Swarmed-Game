#include <cmath>
#include <iostream>

#include "army.h"

Army::Army(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Player* target,
    Texture texture)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _target(target),
      _texture(std::move(texture)) {
          //Spawn enemies from 4 different positions
          std::tuple<int, int> pos1;
          std::tuple<int, int> pos2;
          std::tuple<int, int> pos3;
          std::tuple<int, int> pos4;
          pos1 = std::make_tuple(-50, _screenHeight/2);
          pos2 = std::make_tuple(_screenWidth/2, -50);
          pos3 = std::make_tuple(_screenWidth + 50, _screenHeight/2);
          pos4 = std::make_tuple(_screenWidth/2, _screenHeight + 50);
          _spawnPoints.push_back(pos1);
          _spawnPoints.push_back(pos2);
          _spawnPoints.push_back(pos3);
          _spawnPoints.push_back(pos4);

          //Start spawning cooldown timer
          _spawnTimer.start();
      }

void Army::spawn() {
    //Choose a random Spawning Point
    std::uniform_int_distribution<int> distribution(0, 3);
    int randomPos = distribution(_generator);

    if (_spawnTimer.getTicks() >= 2500) {
        _spawnTimer.start();
        Enemy newEnemy(_spawnPoints[randomPos], &_texture);
        Collider newCollider = {
            newEnemy.getWidth()/2,
            newEnemy.getPosX(),
            newEnemy.getPosY()
        };
        _enemies.push_back(newEnemy);
        _colliders.push_back(newCollider);
        std::cout << "Enemy Spawned!" << std::endl;
    }
}

void Army::move(float timeStep)
{
    if (!_enemies.empty()) {
        for (auto enemy = _enemies.begin(); enemy <= _enemies.end(); enemy++) {
            enemy->updateSpeed(_target->getPosX(), _target->getPosY());
            enemy->move(timeStep);
        }
    }
}

void Army::updateEnemies() {
    //Eventually all enemies will get popped out
    if (!_enemies.empty()) {
        if (_enemies.front().getHealth() < 1) {
            _enemies.pop_front();
            _colliders.pop_front();
        }
    }
}

void Army::updateColliders() {
    if (!_enemies.empty()) {
        for (int i = 0; i < _enemies.size(); i++) {
            _colliders[i].x = _enemies[i].getPosX();
            _colliders[i].y = _enemies[i].getPosY();
        }
    }
}

void Army::render() {
    //Render the remaining enemies
    if (!_enemies.empty()) {
        for (auto enemy = _enemies.begin(); enemy <= _enemies.end(); enemy++) {
            enemy->render();
        }
    }
}

std::deque<Collider>& Army::getColliders() {
    return _colliders;
}