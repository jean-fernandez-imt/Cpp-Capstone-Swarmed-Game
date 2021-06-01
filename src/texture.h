#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

//Texture wrapper class
class Texture {

	public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFromFile(std::string path);
		
		//Deallocates texture
		void release();
		
		//Renders texture at given point
		void render(
            int x, 
            int y, 
            SDL_Rect* crop = nullptr, 
            double angle = 0.0, 
            SDL_Point* center = nullptr, 
            SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* _texture;

		//Image dimensions
		int _width;
		int _height;

};

#endif