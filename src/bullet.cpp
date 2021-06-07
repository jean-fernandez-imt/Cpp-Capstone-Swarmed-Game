#include "bullet.h"

Bullet::Bullet(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Texture texture)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _texture(std::move(texture)),
      _x(100),
      _y(100),
      _dx(0),
      _dy(0),
      _health(0),
      _fired(false) {}

void Bullet::handleEvent(SDL_Event& e) {
    //If mouse event happened
	if(e.type == SDL_MOUSEMOTION 
        || e.type == SDL_MOUSEBUTTONDOWN 
        || e.type == SDL_MOUSEBUTTONUP) {
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

        //Choose actions on mouse event
        switch(e.type){
            case SDL_MOUSEMOTION:
            break;
        
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
        _x = 100;
        _y = 100;
        _dx = 10;
        _health = 1;
    }

    _x += _dx;

    if (_x > _screenWidth) {
        _health = 0;
    }
}

void Bullet::render() {
    //if (_health == 1) {
        _texture.render(_x, _y);
    //}
} 
