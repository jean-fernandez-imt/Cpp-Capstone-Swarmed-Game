#ifndef AIM_H
#define AIM_H

#include <SDL2/SDL.h>
#include "texture.h"

//The mouse button
class Aim {
	public:
		//Initializes internal variables
		Aim(Texture texture);

		//Sets top left position
		void updatePosition(int x, int y);

		//Handles mouse event
		void handleEvent(SDL_Event& e);
	
		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Point _position;
        Texture _texture;
};

#endif