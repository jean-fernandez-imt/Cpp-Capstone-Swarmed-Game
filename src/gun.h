#ifndef GUN_H
#define GUN_H

#include <deque>

#include "texture.h"
#include "player.h"
#include "bullet.h"

//Shoots the bullets of the Player
class Gun {
    public:
        Gun(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Texture texture,
            Player* player);
        
        //Handles mouse event
		void handleEvent(SDL_Event& e);

        void updateGun(SDL_Point aimPos);
        void updateBullets(float timeStep);

        void render();

        std::deque<Bullet*>  getBullets();

    private:
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Designated texture and player
        Texture _texture;
        Player* _player;

        std::deque<Bullet*> _bullets;

        float _posX;
        float _posY;
        float _targetX;
        float _targetY;

        void clearBullets();
};

#endif