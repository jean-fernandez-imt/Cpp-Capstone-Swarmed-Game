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
            Texture texture1,
            Texture texture2,
            Texture texture3,
            Texture texture4,
            Texture texture5,
            Texture texture6);

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

        //Different Enemies Textures
        Texture _texture1;
        Texture _texture2;
        Texture _texture3;
        Texture _texture4;
        Texture _texture5;
        Texture _texture6;

        //For random texture Enemy Spawning
        std::deque<Texture*> _textures;

		//Spawning control
		Timer _spawnTimer;
		std::deque<std::tuple<int, int>> _spawnPoints;

        //Random number generator
        std::random_device _generator;

        std::deque<Enemy*> _enemies;
};

#endif