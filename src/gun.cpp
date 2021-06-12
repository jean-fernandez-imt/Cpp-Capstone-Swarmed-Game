#include <math.h>

#include "gun.h"

Gun::Gun(
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
      _speed(10.0) {}

void Gun::handleEvent(SDL_Event& e) {
    //If mouse event happened
	if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {

        //Choose actions on mouse event
        switch(e.type){    
            case SDL_MOUSEBUTTONDOWN:
            _bullets.emplace_back(
                Bullet(
                    _screenWidth,
                    _screenHeight,
                    &_texture,
                    _x,
                    _y,
                    _dx,
                    _dy,
                    _speed
                )
            );
            break;
            
            case SDL_MOUSEBUTTONUP:
        
            break;
        }
	}
}

void Gun::updateGun() {
    _x = _player->getPosX();
    _y = _player->getPosY();
    updateTarget();
    clearBullets();
}

void Gun::updateTarget() {
    _dx = (sin((_player->getAngle())*M_PI/180.0))*_speed;
    _dy = -(cos((_player->getAngle())*M_PI/180.0))*_speed;
}

void Gun::clearBullets() {
    //Eventually all bullets will get dequeued
    if (!_bullets.empty()) {
        if (_bullets.front().getHealth() < 1) {
            _bullets.pop_front();
        }
    }
}

void Gun::render() {
    if (!_bullets.empty()) {
        for (auto bullet = _bullets.begin(); bullet <= _bullets.end(); bullet++) {
            bullet->fire();
        }
    }
}
