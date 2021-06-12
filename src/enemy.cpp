#include <cmath>

#include "enemy.h"

Enemy::Enemy(
    SpawningPos spawningPos,
	Player* target,
    Texture* texture)
    : _spawningPos(spawningPos),
      _target(target),
      _texture(texture),
      _health(1),
      _width(50),
      _height(50),
      _vel(240),
      _posX(_spawningPos.x),
      _posY(_spawningPos.y),
      _direction(0),
      _velX(0),
      _velY(0) {}

void Enemy::updateDirection() {
    //Make a steadier redirectioning
    if (_target->getPosX() == _posX) {
        if (_target->getPosY() >= _posY) {
            _direction = 180;
        } else if (_target->getPosY() < _posY) {
            _direction = 0;
        }
    } else {
        _direction = 
            (atan2((_target->getPosY() - _posY), (_target->getPosX() - _posX))
            *180
            /M_PI)
            + 90;
    }
}

void Enemy::updateSpeed() {
    _velX = (sin(_direction*M_PI/180.0))*_vel;
    _velY = -(cos(_direction*M_PI/180.0))*_vel;
}

void Enemy::move(float timeStep) {
    updateDirection();
    updateSpeed();
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