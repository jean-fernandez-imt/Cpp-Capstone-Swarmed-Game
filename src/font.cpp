#include <iostream>

#include "font.h"

Font::Font(std::string path, int size) {
	//Loading the font file
    SDL_LogMessage(
		SDL_LOG_CATEGORY_APPLICATION, 
		SDL_LOG_PRIORITY_INFO, 
		"Loading: %s", 
		path.c_str());

    _font = TTF_OpenFont(path.c_str(), size);

    if (_font == NULL) {
        std::cerr << "Unable to load font from: " << path.c_str() << std::endl;
        std::cerr << "SDL2_TTF_Error: " << TTF_GetError() << std::endl;
    }
}

Font::~Font() {
    //Free font if it exists
    if (_font != NULL) {
        TTF_CloseFont(_font);
	    _font = NULL;
    }
}

//Copy constructor
Font::Font(const Font &source) {
	std::cout << "Font: Copy constructor called." << std::endl;
    _font = source._font;
}

//Copy assignment operator
Font &Font::operator=(const Font &source) {
	std::cout << "Font: Copy assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
    _font = source._font;
}

//Move constructor
Font::Font(Font &&source) {
	std::cout << "Font: Move constructor called." << std::endl;
	_font = source._font;
    source._font = NULL;
}

//Move assignment operator
Font &Font::operator=(Font &&source) {
	std::cout << "Font: Move assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
	_font = source._font;
    source._font = NULL;
}

TTF_Font* Font::getFont() {
	return _font;
}