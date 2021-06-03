#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

//Texture wrapper class
class Texture {

	public:
		//Initializes variables
		Texture(SDL_Renderer* renderer);

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		void loadFromFile(std::string path);
		
		//Deallocates texture
		void release();

		SDL_Texture* getTexture();
		
		/*
		//Renders texture at given point
		void render(
            int x, 
            int y, 
            SDL_Rect* crop = NULL, 
            double angle = 0.0, 
            SDL_Point* center = NULL, 
            SDL_RendererFlip flip = SDL_FLIP_NONE);
		*/

	private:
		//The actual hardware texture
		SDL_Texture* _texture;
		SDL_Renderer* _renderer;
};

#endif