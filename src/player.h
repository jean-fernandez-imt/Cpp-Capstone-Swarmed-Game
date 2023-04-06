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

		float getPosX();
		float getPosY();

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

		float _vel;
		
		float _posX; 
        float _posY;

		double _angle;

		float _velX;
        float _velY;

		int _hp;

		//Collider control
		Collider _collider;
		void shiftCollider();
};

#endif