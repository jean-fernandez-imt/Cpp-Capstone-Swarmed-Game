#include <math.h>
#include <iostream>

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
        _x(0.0),
        _y(0.0),
        _dx(0.0),
        _dy(0.0) {}

void Gun::handleEvent(SDL_Event& e) {
	if(e.type == SDL_MOUSEBUTTONDOWN) {
        _bullets.emplace_back(
            new Bullet(
                _screenWidth,
                _screenHeight,
                &_texture,
                _x,
                _y,
                _dx,
                _dy));
	}
}

void Gun::updateGun(SDL_Point aimPos) {
    _x = _player->getPosX();
    _y = _player->getPosY();

    // WIP: Think about what to do with this data
    _dx = static_cast<float>(aimPos.x) - _x;
    _dy = static_cast<float>(aimPos.y) - _y;

    std::cout << "[LOG GUN] _dx: " << _dx << "\n";
    std::cout << "[LOG GUN] _dy: " << _dy << "\n";

    clearBullets();
}

void Gun::updateBullets(float timeStep) {
    //Update the position of the remianing bullets
    if (!_bullets.empty()) {
        for (Bullet* bullet: _bullets) {
            bullet->update(timeStep);
        }
    }
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
            bullet->render();
        }
    }
}

std::deque<Bullet*> Gun::getBullets() {
    return _bullets;
}