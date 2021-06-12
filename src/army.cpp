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
          SpawningPos pos1;
          SpawningPos pos2;
          SpawningPos pos3;
          SpawningPos pos4;
          pos1.x = -50;
          pos1.y = _screenHeight/2;
          pos2.x = _screenWidth/2;
          pos2.y = -50;
          pos3.x = _screenWidth + 50;
          pos3.y = _screenHeight/2;
          pos4.x = _screenWidth/2;
          pos4.y = _screenHeight + 50;
          _spawnPoints.push_back(pos1);
          _spawnPoints.push_back(pos2);
          _spawnPoints.push_back(pos3);
          _spawnPoints.push_back(pos4);

          //Start spawning cooldown timer
          _spawnTimer.start();
      }

void Army::spawn() {
    if (_spawnTimer.getTicks() >= 2000) {
        _spawnTimer.start();
        _enemies.emplace_back(
            Enemy(
                _spawnPoints[0],
                _target,
                &_texture
            )
        );
    }
}

void Army::updateEnemies(float timeStep) {
    //Eventually all enemies will get popped out
    if (!_enemies.empty()) {
        if (_enemies.front().getHealth() < 1) {
            _enemies.pop_front();
        }
        for (auto enemy = _enemies.begin(); enemy <= _enemies.end(); enemy++) {
            enemy->move(timeStep);
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