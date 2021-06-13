#ifndef ARMY_H
#define ARMY_H

#include <SDL2/SDL.h>
#include <deque>
#include <tuple>
#include <random>

#include "texture.h"
#include "player.h"
#include "enemy.h"
#include "timer.h"
#include "collider.h"

class Army {
    public:
		//Initializes the variables
		Army(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Player* target,
            Texture texture);

        //Spawning the enemies
        void spawn();

        //Move the enemies
        void move(float timeStep);

        //Check if the enemy is still alive
        void updateEnemies();

        //Update the status of the colliders
        void updateColliders();

        //Rendering the enemies
        void render();

    private:
        //Screen size references
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Target player
        Player* _target;

        //Borrowed texture
        Texture _texture;

		//Spawning control
		Timer _spawnTimer;
		std::deque<std::tuple<int, int>> _spawnPoints;

        //Random number generator
        std::random_device _generator;

        //Existing enemies and colliders
        std::deque<Enemy> _enemies;
        std::deque<Collider> _colliders;
};

#endif