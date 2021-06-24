#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

//Wrapper class for TTF_Font objects
class Font {
	public:
		Font(SDL_Renderer* renderer, std::string path, int size);

		~Font();

		//Applying Rule of 5
		Font(const Font &source);
		Font &operator=(const Font &source);
		Font(Font &&source);
		Font &operator=(Font &&source);

		void loadFromRenderedText(std::string text, SDL_Color color);

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
		//The actual font
        TTF_Font* _font;

        //Texture constantly changes
		SDL_Texture* _texture;
		SDL_Renderer* _renderer;

		std::size_t _width;
		std::size_t _height;

		//Deallocates elements
		void releaseTexture();
        void releaseFont();
};

#endif