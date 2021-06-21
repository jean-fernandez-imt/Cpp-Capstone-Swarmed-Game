#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <deque>
#include <random>

#include "texture.h"

//Controls the random backgrounds
class Background {
    public:
        Background(
            Texture background1,
            Texture background2,
            Texture background3,
            Texture background4,
            Texture background5);
        
        Texture* getRandomBackgound();

    private:
        Texture _background1;
        Texture _background2;
        Texture _background3;
        Texture _background4;
        Texture _background5;

        //For random backgrounds
        std::deque<Texture*> _backgrounds;

        //Random number generator
        std::random_device _generator;
};

#endif