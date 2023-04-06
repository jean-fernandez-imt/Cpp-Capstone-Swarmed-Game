#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <tuple>

#include "texture.h"
#include "collider.h"

//Soldier of the Enemy Army
class Enemy {
    public:
		Enemy(
			std::tuple<int, int> spawningPos,
            Texture* texture);
		
		//Redirectionates the enemy
		void updateSpeed(int targetX, int targetY);

		void move(float timeStep);

		void render();

		int getHealth();

		int getWidth();
		int getHeight();

		float getPosX();
		float getPosY();

		Collider& getCollider();

		//In case of collision
		void takeHit();

    private:
        //Borrowed from Army
        Texture* _texture;

		int _health;

		const std::size_t _width;
		const std::size_t _height;

		//Vectorial velocity (for calculations)
		float _vel;
		
		float _posX; 
        float _posY;

		double _direction;

		//Components of vectorial velocity
		float _velX;
        float _velY;

		//Collider control
		Collider _collider;
		void shiftCollider();
};

#endif