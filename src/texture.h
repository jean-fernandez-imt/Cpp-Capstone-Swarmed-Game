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

		//Applying Rule of 5
		Texture(const Texture &source);
		Texture &operator=(const Texture &source);
		Texture(Texture &&source);
		Texture &operator=(Texture &&source);

		//Deallocates texture
		void release();

		//Loads image at specified path
		void loadFromFile(std::string path);

		//Renders texture at given point
		void render(
            int x, 
            int y, 
            SDL_Rect* crop = NULL, 
            double angle = 0.0, 
            SDL_Point* center = NULL, 
            SDL_RendererFlip flip = SDL_FLIP_NONE);

		SDL_Texture* getTexture();
		std::size_t getWidth();
		std::size_t getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* _texture;
		SDL_Renderer* _renderer;

		std::size_t _width;
		std::size_t _height;
};

#endif