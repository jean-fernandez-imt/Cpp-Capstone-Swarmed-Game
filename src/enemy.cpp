#include <cmath>

#include "enemy.h"

Enemy::Enemy(
    std::tuple<int, int> spawningPos,
    Texture* texture)
    : _texture(texture),
      _health(1),
      _width(50),
      _height(50),
      _vel(240),
      _posX(std::get<0>(spawningPos)),
      _posY(std::get<1>(spawningPos)),
      _direction(90),
      _velX(0),
      _velY(0) {}

void Enemy::updateSpeed(int targetX, int targetY) {
    //Redirect the enemy to the target
    if (targetX == _posX) {
        if (targetY >= _posY) {
            _direction = 180;
        } else if (targetY < _posY) {
            _direction = 0;
        }
    } else {
        _direction = 
            (atan2((targetY - _posY), (targetX - _posX))
            *180
            /M_PI)
            + 90;
    }

    //Update speed
    _velX = (sin(_direction*M_PI/180.0))*_vel;
    _velY = -(cos(_direction*M_PI/180.0))*_vel;
}

void Enemy::move(float timeStep) {
    //Move the enemy left or right
    _posX += _velX*timeStep;
    //Move the enemy up or down
    _posY += _velY*timeStep;
}

void Enemy::render() {
    //Show the enemy if it is still alive
    if (_health >= 1) {
    	_texture->render(_posX - _width/2, _posY - _height/2, NULL, _direction);
    }
}

int Enemy::getHealth() {
    return _health;
}