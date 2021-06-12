#ifndef ARMY_H
#define ARMY_H

#include <SDL2/SDL.h>
#include <deque>
#include <tuple>

#include "texture.h"
#include "player.h"
#include "enemy.h"
#include "timer.h"

class Army {
    public:
		//Initializes the variables
		Army(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Player* _target,
            Texture texture);

        //Spawning the enemies
        void spawn();

        //Check if the enemy is still alive
        void updateEnemies(float timeStep);

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

        //Existing enemies
        std::deque<Enemy> _enemies;
};

#endif