#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

//Wrapper class for SDL_Texture objects
class Texture {
	public:
		Texture(SDL_Renderer* renderer);

		~Texture();

		//Applying Rule of 5
		Texture(const Texture &source);
		Texture &operator=(const Texture &source);
		Texture(Texture &&source);
		Texture &operator=(Texture &&source);

		void loadFromFile(std::string path);

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

		//Deallocates texture
		void releaseTexture();
};

#endif