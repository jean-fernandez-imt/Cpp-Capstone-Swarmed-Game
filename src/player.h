#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "texture.h"
#include "collider.h"

//The Main Player
class Player {
    public:
		Player(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Texture texture);

		//Handles keyboard event
		void handleEvent(SDL_Event& e);
		
		//Rotates the player
		void updateAngle(SDL_Point aimPos);

		void move(float timeStep);

		void render();

		int getPosX();
		int getPosY();

		double getAngle();

		int getHP();

		Collider& getCollider();

		//In case of collision
		void takeHit();

    private:
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        Texture _texture;

		const std::size_t _width;
		const std::size_t _height;

		const std::size_t _vel;
		
		int _posX; 
        int _posY;

		double _angle;

		int _velX;
        int _velY;

		int _hp;

		//Collider control
		Collider _collider;
		void shiftCollider();
};

#endif