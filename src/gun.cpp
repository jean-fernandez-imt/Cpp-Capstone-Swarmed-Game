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
        _posX(0.0),
        _posY(0.0),
        _targetX(0.0),
        _targetY(0.0) {}

void Gun::handleEvent(SDL_Event& e) {
	if(e.type == SDL_MOUSEBUTTONDOWN) {
        _bullets.emplace_back(
            new Bullet(
                _screenWidth,
                _screenHeight,
                &_texture,
                _posX,
                _posY,
                _targetX,
                _targetY));
	}
}

void Gun::updateGun(SDL_Point aimPos) {
    _posX = _player->getPosX();
    _posY = _player->getPosY();

    _targetX = static_cast<float>(aimPos.x);
    _targetY = static_cast<float>(aimPos.y);

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