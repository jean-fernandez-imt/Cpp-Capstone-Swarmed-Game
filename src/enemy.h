#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <tuple>

#include "texture.h"
#include "player.h"

class Enemy {
    public:
		//Initializes the variables
		Enemy(
			std::tuple<int, int> spawningPos,
			Player* target,
            Texture* texture);
		
		//Redirectionates the enemy
		void updateDirection();
		void updateSpeed();

		//Moves the enemy
		void move(float timeStep);

		//Shows the enemy on the screen
		void render();

		//Verify if the enemy is still alive
		int getHealth();

    private:
		//Target player
		Player* _target;

        //Designated texture
        Texture* _texture;

		//For checking enemy existence
		int _health;

		//The dimensions of the enemy
		const std::size_t _width;
		const std::size_t _height;

		//Maximum axis velocity of the enemy
		const std::size_t _vel;
		
        //The X and Y offsets of the enemy
		int _posX; 
        int _posY;

		//The enemy should face the target
		double _direction;

		//The velocity of the enemy
		int _velX;
        int _velY;
};

#endif