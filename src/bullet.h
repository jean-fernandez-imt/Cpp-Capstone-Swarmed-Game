#ifndef BULLET_H
#define BULLET_H

#include "texture.h"
#include "player.h"

class Bullet {
    public:
        Bullet(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Texture texture,
            Player* player);
        
        //Handles mouse event
		void handleEvent(SDL_Event& e);

        void fire();
        void updateTarget();

        void render();

    private:
        //Screen size references
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Designated texture and player
        Texture _texture;
        Player* _player;

        //Movement control variables
        int _x;
        int _y;
        double _dx;
        double _dy;
        double _speed;
        int _health;
        bool _fired;
};

#endif