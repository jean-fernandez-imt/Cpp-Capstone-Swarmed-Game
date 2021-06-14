#include <cmath>

#include "parameters.h"
#include "enemy.h"

Enemy::Enemy(
    std::tuple<int, int> spawningPos,
    Texture* texture)
    : _texture(texture),
      _health(ENEMY_HEALTH),
      _width(ENEMY_WIDTH),
      _height(ENEMY_HEIGHT),
      _vel(ENEMY_VELOCITY),
      _posX(std::get<0>(spawningPos)),
      _posY(std::get<1>(spawningPos)),
      _direction(0),
      _velX(0),
      _velY(0) {
          _collider.r = _width/2;
          _collider.x = _posX;
          _collider.y = _posY;
      }

void Enemy::updateSpeed(int targetX, int targetY) {
    //Redirects the enemy to the target
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

    //Update velocity components
    _velX = (sin(_direction*M_PI/180.0))*_vel;
    _velY = -(cos(_direction*M_PI/180.0))*_vel;
}

void Enemy::move(float timeStep) {
    _posX += _velX*timeStep;
    _posY += _velY*timeStep;

    shiftCollider();
}

void Enemy::render() {
    //Shows the enemy if it is still alive
    if (_health > 0) {
    	_texture->render(_posX - _width/2, _posY - _height/2, NULL, _direction);
    }
}

int Enemy::getHealth() {
    return _health;
}

int Enemy::getWidth() {
    return _width;
}

int Enemy::getHeight() {
    return _height;
}

int Enemy::getPosX() {
    return _posX;
}

int Enemy::getPosY() {
    return _posY;
}

Collider& Enemy::getCollider() {
    return _collider;
}

void Enemy::takeHit() {
    _health -= 1;
}

void Enemy::shiftCollider() {
    _collider.x = _posX;
    _collider.y = _posY;
}