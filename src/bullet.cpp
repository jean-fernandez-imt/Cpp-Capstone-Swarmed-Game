#include <math.h>

#include "parameters.h"
#include "bullet.h"

Bullet::Bullet(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture* texture,
    float posX,
    float posY,
    float targetX,
    float targetY)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(texture),
      _width(BULLET_WIDTH),
      _height(BULLET_HEIGHT),
      _posX(posX),
      _posY(posY),
      _targetX(targetX),
      _targetY(targetY),
      _speed(static_cast<float>(BULLET_SPEED)),
      _health(BULLET_HEALTH) {
          _collider.r = static_cast<float>(_width/2);
          _collider.x = _posX;
          _collider.y = _posY;

          //Define the direction of the bullet from the initial data
          double direction = 0.0;

          if (_targetX == _posX) {
              if (_targetY >= _posY) {
                  direction = 180.0;
              } else if (_targetY < _posY) {
                  direction = 0.0;
              }
          } else if (_targetY == _posY) {
              if (_targetX >= _posX) {
                  direction = 90.0;
              } else if (_targetX < _posX) {
                direction = 270.0;
              }
          } else {
              direction = 
                  (atan2((_targetY - _posY), (_targetX - _posX))
                  *180.0
                  /M_PI)
                  + 90.0;
          }

          //Update speed components
          _speedX = (sin(direction*M_PI/180.0))*_speed;
          _speedY = -(cos(direction*M_PI/180.0))*_speed;
      }

void Bullet::update(float timeStep) {
    _posX += _speedX*timeStep;
    _posY += _speedY*timeStep;

    if (_posX > _screenWidth || _posX < 0 || _posY > _screenHeight || _posY < 0) {
        _health = 0;
    }

    shiftCollider();
}

void Bullet::render() {
    if (_health > 0) {
        _texture->render(_posX - _width/2, _posY - _height/2);
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

float Bullet::getX() {
    return _posX;
}

float Bullet::getY() {
    return _posY;
}

Collider& Bullet::getCollider() {
    return _collider;
}

void Bullet::takeHit() {
    _health -= 1;
}

void Bullet::shiftCollider() {
    _collider.x = _posX;
    _collider.y = _posY;
}
