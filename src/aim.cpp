#include "aim.h"

Aim::Aim(Texture texture): _texture(std::move(texture)) {
	_position.x = 0;
	_position.y = 0;
}

void Aim::updatePosition(int x, int y) {
	_position.x = x;
	_position.y = y;
}

void Aim::handleEvent(SDL_Event& e) {
	//If mouse event happened
	if(e.type == SDL_MOUSEMOTION 
        || e.type == SDL_MOUSEBUTTONDOWN 
        || e.type == SDL_MOUSEBUTTONUP) {
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

        //Update mouse position
        updatePosition(x, y);

        //Choose actions on mouse event
        switch(e.type){
            case SDL_MOUSEMOTION:
            break;
        
            case SDL_MOUSEBUTTONDOWN:
            break;
            
            case SDL_MOUSEBUTTONUP:
            break;
        }
	}
}
	
void Aim::render() {
	_texture.render(
        _position.x - (_texture.getWidth()/2), 
        _position.y- (_texture.getHeight()/2));
}