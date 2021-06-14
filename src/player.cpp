#include <cmath>

#include "parameters.h"
#include "player.h"

Player::Player(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture texture)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(std::move(texture)),
      _width(PLAYER_WIDTH),
      _height(PLAYER_HEIGHT),
      _vel(PLAYER_VELOCITY),
      _posX(_screenWidth/2),
      _posY(_screenHeight/2),
      _angle(0),
      _velX(0),
      _velY(0),
      _hp(PLAYER_HP) {
          _collider.r = _width/2;
          _collider.x = _posX;
          _collider.y = _posY;
      }

void Player::handleEvent(SDL_Event& e) {
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_w: _velY -= _vel; break;
            case SDLK_s: _velY += _vel; break;
            case SDLK_a: _velX -= _vel; break;
            case SDLK_d: _velX += _vel; break;
        }
    } else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        switch( e.key.keysym.sym ) {
            case SDLK_w: _velY += _vel; break;
            case SDLK_s: _velY -= _vel; break;
            case SDLK_a: _velX += _vel; break;
            case SDLK_d: _velX -= _vel; break;
        }
    }
}

void Player::updateAngle(SDL_Point aimPos) {
    //Make a steadier aim
    if (aimPos.x == _posX) {
        if (aimPos.y >= _posY) {
            _angle = 180;
        } else if (aimPos.y < _posY) {
            _angle = 0;
        }
    } else {
        _angle = 
            (atan2((aimPos.y - _posY), (aimPos.x - _posX))
            *180
            /M_PI)
            + 90;
    }
}

void Player::move(float timeStep) {
    _posX += _velX*timeStep;

    //If the player went too far to the left or right
    if(_posX < _width/2) {
        _posX = _width/2;
    } else if (_posX > _screenWidth - _width/2) {
        _posX = _screenWidth - _width/2;
    }

    _posY += _velY*timeStep;

    //If the player went too far up or down
    if(_posY < _height/2) {
        _posY = _height/2;
    } else if (_posY > _screenHeight - _height/2) {
        _posY = _screenHeight - _height/2;
    }

    shiftCollider();
}

void Player::render() {
	_texture.render(_posX - _width/2, _posY - _height/2, NULL, _angle);
} 

int Player::getPosX() {
    return _posX;
}

int Player::getPosY() {
    return _posY;
}

double Player::getAngle() {
    return _angle;
}

int Player::getHP() {
    return _hp;
}

Collider& Player::getCollider() {
    return _collider;
}

void Player::takeHit() {
    _hp -= 1;
}

void Player::shiftCollider() {
    _collider.x = _posX;
    _collider.y = _posY;
}