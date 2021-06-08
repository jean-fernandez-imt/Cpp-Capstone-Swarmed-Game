#ifndef BULLET_H
#define BULLET_H

#include "texture.h"

class Bullet {
    public:
        Bullet(
            const std::size_t screenWidth, 
            const std::size_t screenHeight,
            Texture* texture,
            int x,
            int y,
            double dx,
            double dy,
            double speed);

        void fire();

        int getHealth();

    private:
        //Screen size references
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Borrowed Texture
        Texture* _texture;

        //Movement control variables
        int _x;
        int _y;
        double _dx;
        double _dy;
        double _speed;
        int _health;
};

#endif