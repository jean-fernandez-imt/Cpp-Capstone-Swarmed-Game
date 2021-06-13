#include <math.h>

#include "bullet.h"

Bullet::Bullet(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture* texture,
    int x,
    int y,
    double dx,
    double dy,
    double speed)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(texture),
      _width(10),
      _height(10),
      _x(x),
      _y(y),
      _dx(dx),
      _dy(dy),
      _speed(speed),
      _health(1) {}

void Bullet::fire() {
    _x += _dx;
    _y += _dy;

    if (_x > _screenWidth || _x < 0 || _y > _screenHeight || _y <0) {
        _health = 0;
    }

    if (_health == 1) {
        _texture->render(_x, _y);
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

void Bullet::takeHit() {
    _health -= 1;
}
