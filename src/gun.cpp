#include <math.h>

#include "parameters.h"
#include "gun.h"

Gun::Gun(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture texture, 
    Player* player)
      : _screenWidth(screenWidth),
        _screenHeight(screenHeight),
        _texture(std::move(texture)),
        _player(player),
        _x(0),
        _y(0),
        _dx(0.0),
        _dy(0.0),
        _speed(GUN_BULLET_SPEED) {}

void Gun::handleEvent(SDL_Event& e) {
	if(e.type == SDL_MOUSEBUTTONDOWN) {
        Bullet* newBullet = 
            new Bullet(
                _screenWidth,
                _screenHeight,
                &_texture,
                _x,
                _y,
                _dx,
                _dy,
                _speed);
        _bullets.push_back(newBullet);
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
    //Delete the used bullets
    if (!_bullets.empty()) {
        for (int i = 0; i < _bullets.size(); i++) {
            if (_bullets[i]->getHealth() < 1) {
                delete _bullets[i];
                _bullets.erase(_bullets.begin() + i);
            }
        }
    }
}

void Gun::render() {
    //Render the remaining bullets
    if (!_bullets.empty()) {
        for (Bullet* bullet: _bullets) {
            bullet->fire();
        }
    }
}

std::deque<Bullet*> Gun::getBullets() {
    return _bullets;
}