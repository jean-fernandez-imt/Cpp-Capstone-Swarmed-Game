#ifndef MEDIA_H
#define MEDIA_H

#include <SDL2/SDL.h>
#include <vector>

#include "texture.h"

// Class for loading textures needed for the game
class Media {
    public:
        Media(SDL_Renderer* renderer);
        ~Media();

        void loadMedia();
        bool checkMedia();

        std::vector<Texture*> getTextures();

    private:
        std::vector<Texture*> _textures;
        SDL_Renderer* _renderer;
};

#endif