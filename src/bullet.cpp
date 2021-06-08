#include <math.h>

#include "bullet.h"

Bullet::Bullet(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture texture, Player* player)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(std::move(texture)),
      _player(player),
      _x(0),
      _y(0),
      _dx(0.0),
      _dy(0.0),
      _speed(10.0),
      _health(0),
      _fired(false) {}

void Bullet::handleEvent(SDL_Event& e) {
    //If mouse event happened
	if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {

        //Choose actions on mouse event
        switch(e.type){    
            case SDL_MOUSEBUTTONDOWN:
            _fired = true;
            break;
            
            case SDL_MOUSEBUTTONUP:
            _fired = false;
            break;
        }
	}
}

void Bullet::fire() {
    if ((_health == 0) && _fired) {
        _x = _player->getPosX();
        _y = _player->getPosY();
        updateTarget();
        _health = 1;
    }

    _x += _dx;
    _y += _dy;

    if (_x > _screenWidth || _x < 0 || _y > _screenHeight || _y <0) {
        _health = 0;
    }
}

void Bullet::updateTarget() {
    _dx = (sin((_player->getAngle())*M_PI/180.0))*_speed;
    _dy = -(cos((_player->getAngle())*M_PI/180.0))*_speed;
}

void Bullet::render() {
    if (_health == 1) {
        _texture.render(_x, _y);
    }
} 
