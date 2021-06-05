#include "player.h"

Player::Player(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture texture)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(std::move(texture)),
      _width(100),
      _height(100),
      _vel(320),
      _posX(0),
      _posY(0),
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

void Player::move(float timeStep) {
    //Move the player left or right
    _posX += _velX*timeStep;

    //If the player went too far to the left or right
    if(_posX < 0) {
        _posX = 0;
    } else if (_posX > _screenWidth - _width) {
        //Move back
        _posX = _screenWidth - _width;
    }

    //Move the player up or down
    _posY += _velY*timeStep;

    //If the player went too far up or down
    if(_posY < 0) {
        _posY = 0;
    } else if (_posY > _screenHeight - _height) {
        //Move back
        _posY = _screenHeight - _height;
    }
}

void Player::render() {
    //Show the player
	_texture.render(_posX, _posY);
}