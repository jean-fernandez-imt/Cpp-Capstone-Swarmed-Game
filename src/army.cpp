#include <cmath>
#include <iostream>

#include "parameters.h"
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
          pos1 = std::make_tuple(
              -ARMY_SPAWN_SCREEN_OFFSET, 
              _screenHeight/2);
          pos2 = std::make_tuple(
              _screenWidth/2, 
              -ARMY_SPAWN_SCREEN_OFFSET);
          pos3 = std::make_tuple(
              _screenWidth 
              + ARMY_SPAWN_SCREEN_OFFSET, 
              _screenHeight/2);
          pos4 = std::make_tuple(
              _screenWidth/2, 
              _screenHeight 
              + ARMY_SPAWN_SCREEN_OFFSET);
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

    if (_spawnTimer.getTicks() >= ARMY_SPAWN_COOLDOWN_TIME) {
        _spawnTimer.start();
        Enemy* newEnemy = new Enemy(_spawnPoints[randomPos], &_texture);
        _enemies.push_back(newEnemy);
        std::cout << "Enemy Spawned!" << std::endl;
    }
}

void Army::move(float timeStep)
{
    if (!_enemies.empty()) {
        for (Enemy* enemy: _enemies) {
            enemy->updateSpeed(_target->getPosX(), _target->getPosY());
            enemy->move(timeStep);
        }
    }
}

void Army::updateEnemies() {
    //Delete the dead enemies
    if (!_enemies.empty()) {
        for (int i = 0; i < _enemies.size(); i++) {
            if (_enemies[i]->getHealth() < 1) {
                delete _enemies[i];
                _enemies.erase(_enemies.begin() + i);
            }
        }
    }
}

void Army::render() {
    //Render the remaining enemies
    if (!_enemies.empty()) {
        for (Enemy* enemy: _enemies) {
            enemy->render();
        }
    }
}

std::deque<Enemy*> Army::getEnemies() {
    return _enemies;
}