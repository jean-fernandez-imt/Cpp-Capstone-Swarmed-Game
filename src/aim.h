#ifndef AIM_H
#define AIM_H

#include <SDL2/SDL.h>
#include "texture.h"

//The player's scope
class Aim {
	public:
		Aim(Texture texture);

		//Handles mouse event
		void handleEvent(SDL_Event& e);
	
		void render();

		SDL_Point getPosition();

	private:
		SDL_Point _position;
        Texture _texture;
};

#endif