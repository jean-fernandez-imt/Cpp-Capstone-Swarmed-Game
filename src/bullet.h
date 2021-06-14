#ifndef BULLET_H
#define BULLET_H

#include "texture.h"
#include "collider.h"

//The bullets shot by the player
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

        int getWidth();
        int getHeight();
        
        int getX();
        int getY();

        Collider& getCollider();

        //In case of collision
        void takeHit();

    private:
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Borrowed from Gun
        Texture* _texture;

        int _width;
        int _height;

        int _x;
        int _y;
        double _dx;
        double _dy;
        double _speed;
        int _health;

        //Collider control
        Collider _collider;
        void shiftCollider();
};

#endif