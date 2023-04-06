#include <math.h>
#include <iostream>

#include "parameters.h"
#include "bullet.h"

Bullet::Bullet(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture* texture,
    int x,
    int y,
    double dx,
    double dy)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(texture),
      _width(BULLET_WIDTH),
      _height(BULLET_HEIGHT),
      _x(x),
      _y(y),
      _angle(0),
      _dx(dx),
      _dy(dy),
      _speed(BULLET_SPEED),
      _health(BULLET_HEALTH) {
          _collider.r = _width/2;
          _collider.x = _x;
          _collider.y = _y;
      }

void Bullet::update(float timeStep) {
    _x += _speed*timeStep;
    _y += _speed*timeStep;

    std::cout << "[LOG BULLET] timeStep: " << timeStep << "\n";

    if (_x > _screenWidth || _x < 0 || _y > _screenHeight || _y <0) {
        _health = 0;
    }

    shiftCollider();
}

void Bullet::render() {
    if (_health > 0) {
        _texture->render(_x - _width/2, _y - _height/2, NULL, _angle);
    }
}

int Bullet::getHealth() {
    return _health;
}

int Bullet::getWidth() {
    return _width;
}

int Bullet::getHeight() {
    return _height;
}

int Bullet::getX() {
    return _x;
}

int Bullet::getY() {
    return _y;
}

Collider& Bullet::getCollider() {
    return _collider;
}

void Bullet::takeHit() {
    _health -= 1;
}

void Bullet::shiftCollider() {
    _collider.x = _x;
    _collider.y = _y;
}
