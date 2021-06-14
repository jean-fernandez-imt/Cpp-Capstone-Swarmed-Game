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

//Spawns the player's enemies
class Army {
    public:
		Army(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Player* target,
            Texture texture);

        void spawn();

        //Move the whole enemy fleet
        void move(float timeStep);

        //Check if an enemy is still alive
        void updateEnemies();

        void render();

        std::deque<Enemy*> getEnemies();

    private:
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Target player
        Player* _target;

        Texture _texture;

		//Spawning control
		Timer _spawnTimer;
		std::deque<std::tuple<int, int>> _spawnPoints;

        //Random number generator
        std::random_device _generator;

        std::deque<Enemy*> _enemies;
};

#endif