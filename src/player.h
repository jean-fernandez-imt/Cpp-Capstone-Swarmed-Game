#ifndef PLAYER_h
#define PLAYER_H

#include <SDL2/SDL.h>

#include "texture.h"

class Player {
    public:
		//Initializes the variables
		Player(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Texture texture);

		//Takes key presses and adjusts the player's velocity
		void handleEvent(SDL_Event& e);
		
		//Rotates the player
		void updateAngle(SDL_Point aimPos);

		//Moves the player
		void move(float timeStep);

		//Shows the player on the screen
		void render();

		//Get the position of the player
		int getPosX();
		int getPosY();

		//Get the angle of the player
		double getAngle();

    private:
        //Screen size references
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Designated texture
        Texture _texture;

        //The dimensions of the player
		const std::size_t _width;
		const std::size_t _height;

		//Maximum axis velocity of the player
		const std::size_t _vel;
		
        //The X and Y offsets of the player
		int _posX; 
        int _posY;

		//The angle of the player respect aim
		double _angle;

		//The velocity of the player
		int _velX;
        int _velY;
};

#endif