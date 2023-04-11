#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

//Wrapper class for TTF_Font objects
class Font {
	public:
		Font(std::string path, int size, SDL_Renderer* renderer);

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

		TTF_Font* getFont();
        std::size_t getWidth();
		std::size_t getHeight();

	private:
		//The actual font
        TTF_Font* _font;

        //Texture to render the text
        SDL_Texture* _text;
        SDL_Renderer* _renderer;

		std::size_t _width;
		std::size_t _height;

		//Deallocates text texture
		void releaseText();
};

#endif