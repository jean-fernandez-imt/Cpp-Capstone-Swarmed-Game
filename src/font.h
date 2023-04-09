#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

//Wrapper class for TTF_Font objects
class Font {
	public:
		Font(std::string path, int size);

		~Font();

		//Applying Rule of 5
		Font(const Font &source);
		Font &operator=(const Font &source);
		Font(Font &&source);
		Font &operator=(Font &&source);

		TTF_Font* getFont();

	private:
		//The actual font
        TTF_Font* _font;
};

#endif