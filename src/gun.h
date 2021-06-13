#ifndef GUN_H
#define GUN_H

#include <deque>

#include "texture.h"
#include "player.h"
#include "bullet.h"

class Gun {
    public:
        Gun(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Texture texture,
            Player* player);
        
        //Handles mouse event
		void handleEvent(SDL_Event& e);

        void updateGun();

        void render();

        std::deque<Bullet*>  getBullets();

    private:
        //Screen size references
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Designated texture and player
        Texture _texture;
        Player* _player;

        //Bullets and colliders currently on screen
        std::deque<Bullet*> _bullets;

        //Movement control variables
        int _x;
        int _y;
        double _dx;
        double _dy;
        double _speed;

        void updateTarget();
        void clearBullets();
};

#endif