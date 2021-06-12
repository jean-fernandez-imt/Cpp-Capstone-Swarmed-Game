#include <cmath>

#include "player.h"

Player::Player(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture texture)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(std::move(texture)),
      _width(80),
      _height(80),
      _vel(320),
      _posX(_screenWidth/2),
      _posY(_screenHeight/2),
      _angle(0),
      _velX(0),
      _velY(0) {}

void Player::handleEvent(SDL_Event& e) {
    //If a key was pressed
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
    //Avoid division by 0
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
    //Move the player left or right
    _posX += _velX*timeStep;

    //If the player went too far to the left or right
    if(_posX < _width/2) {
        _posX = _width/2;
    } else if (_posX > _screenWidth - _width/2) {
        //Move back
        _posX = _screenWidth - _width/2;
    }

    //Move the player up or down
    _posY += _velY*timeStep;

    //If the player went too far up or down
    if(_posY < _height/2) {
        _posY = _height/2;
    } else if (_posY > _screenHeight - _height/2) {
        //Move back
        _posY = _screenHeight - _height/2;
    }
}

void Player::render() {
    //Show the player
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