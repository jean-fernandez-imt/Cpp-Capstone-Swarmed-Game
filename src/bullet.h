#ifndef BULLET_H
#define BULLET_H

#include "texture.h"

class Bullet {
    public:
        Bullet(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Texture texture);
        
        //Handles mouse event
		void handleEvent(SDL_Event& e);

        void fire();

        void render();

    private:
        //Screen size references
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Designated texture
        Texture _texture;

        //Movement control variables
        int _x;
        int _y;
        int _dx;
        int _dy;
        int _health;
        bool _fired;
};

#endif