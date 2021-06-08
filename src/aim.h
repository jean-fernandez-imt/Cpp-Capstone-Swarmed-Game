#ifndef AIM_H
#define AIM_H

#include <SDL2/SDL.h>
#include "texture.h"

//The marksman
class Aim {
	public:
		//Initializes internal variables
		Aim(Texture texture);

		//Handles mouse event
		void handleEvent(SDL_Event& e);
	
		//Shows button sprite
		void render();

		SDL_Point getPosition();

	private:
		//Top left position
		SDL_Point _position;
        Texture _texture;
};

#endif