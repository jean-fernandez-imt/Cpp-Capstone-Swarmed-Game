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
            float posX,
            float posY,
            float targetX,
            float targetY);

        void update(float timeStep);
        void render();

        int getHealth();

        int getWidth();
        int getHeight();
        
        float getX();
        float getY();

        Collider& getCollider();

        //In case of collision
        void takeHit();

    private:
        const std::size_t _screenWidth;
		const std::size_t _screenHeight;

        //Borrowed from Gun
        Texture* _texture;

        const std::size_t _width;
		const std::size_t _height;

		float _speed;

        float _posX;
        float _posY;

        float _targetX;
        float _targetY;

        float _speedX;
        float _speedY;

        int _health;

        //Collider control
        Collider _collider;
        void shiftCollider();
};

#endif