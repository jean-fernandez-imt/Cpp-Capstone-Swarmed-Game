#include "player.h"

Player::Player(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture* texture)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(texture),
      _width(100),
      _height(100),
      _vel(10),
      _posX(0),
      _posY(0),
      _velX(0),
      _velY(0) {}

void Player::handleEvent(SDL_Event& e) {
    //If a key was pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_UP: _velY -= _vel; break;
            case SDLK_DOWN: _velY += _vel; break;
            case SDLK_LEFT: _velX -= _vel; break;
            case SDLK_RIGHT: _velX += _vel; break;
        }
    } else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP: _velY += _vel; break;
            case SDLK_DOWN: _velY -= _vel; break;
            case SDLK_LEFT: _velX += _vel; break;
            case SDLK_RIGHT: _velX -= _vel; break;
        }
    }
}

void Player::move() {
    //Move the player left or right
    _posX += _velX;

    //If the player went too far to the left or right
    if((_posX < 0) || (_posX + _width > _screenWidth)) {
        //Move back
        _posX -= _velX;
    }

    //Move the player up or down
    _posY += _velY;

    //If the player went too far up or down
    if((_posY < 0) || (_posY + _vel > _screenHeight)) {
        //Move back
        _posY -= _velY;
    }
}

void Player::render() {
    //Show the player
	_texture->render(_posX, _posY);
}