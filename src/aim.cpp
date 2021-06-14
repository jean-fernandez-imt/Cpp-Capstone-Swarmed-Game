#include "parameters.h"
#include "aim.h"

Aim::Aim(Texture texture): _texture(std::move(texture)) {
	_position.x = AIM_START_POS_X;
	_position.y = AIM_START_POS_Y;
}

void Aim::handleEvent(SDL_Event& e) {
	if(e.type == SDL_MOUSEMOTION) {
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Update scope's position
		_position.x = x;
		_position.y = y;
	}
}

void Aim::render() {
	_texture.render(
        _position.x - (_texture.getWidth()/2), 
        _position.y - (_texture.getHeight()/2));
}

SDL_Point Aim::getPosition() {
	return _position;
}