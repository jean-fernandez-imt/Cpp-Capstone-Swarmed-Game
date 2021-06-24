#include <iostream>

#include "font.h"

Font::Font(SDL_Renderer* renderer, std::string path, int size)
: _renderer(renderer) {
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

    _texture = NULL;
	_width = 0;
	_height = 0;
}

Font::~Font() {
	release();
}

//Copy constructor
Font::Font(const Font &source) {
	std::cout << "Font: Copy constructor called." << std::endl;
    _font = source._font;
    _texture = NULL;
	_renderer = source._renderer;
	_width = 0;
	_height = 0;
}

//Copy assignment operator
Font &Font::operator=(const Font &source) {
	std::cout << "Font: Copy assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
    _font = source._font;
    _texture = NULL;
	_renderer = source._renderer;
	_width = 0;
	_height = 0;
}

//Move constructor
Font::Font(Font &&source) {
	std::cout << "Font: Move constructor called." << std::endl;
	_font = source._font;
    _texture = NULL;
	_renderer = source._renderer;
	_width = 0;
	_height = 0;
    source._font = NULL;
	source._texture = NULL;
	source._renderer = NULL;
	source._width = 0;
	source._height = 0;
}

//Move assignment operator
Font &Font::operator=(Font &&source) {
	std::cout << "Font: Move assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
	_font = source._font;
    _texture = NULL;
	_renderer = source._renderer;
	_width = 0;
	_height = 0;
    source._font = NULL;
	source._texture = NULL;
	source._renderer = NULL;
	source._width = 0;
	source._height = 0;
}

void Font::release() {
    //Free font if it exists
    if (_font != NULL) {
        TTF_CloseFont(_font);
	    _font = NULL;
    }

	//Free texture if it exists
	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
		_texture = NULL;
        _renderer = NULL;
        _width = 0;
        _height = 0;
	}
}

void Font::loadFromRenderedText(std::string text, SDL_Color color) {
	//Get rid of preexisting texture
	release();

	//Render text surface
	SDL_Surface* textSurface = 
        TTF_RenderText_Solid(
            _font,
            text.c_str(),
            color);

	if (textSurface == NULL) {
        std::cerr << "Unable to render text surface!" << std::endl;
        std::cerr << "SDL2_TTF_Error: " << TTF_GetError() << std::endl;
	}

    //Create texture from surface pixels
    _texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
    
    if (_texture == NULL) {
        std::cerr << "Unable to create texture from rendered text!" << std::endl;
        std::cerr << "SDL2_Error: " << SDL_GetError() << std::endl;
    } else {
		_width = textSurface->w;
		_height = textSurface->h;
	}

    SDL_FreeSurface(textSurface);
}

void Font::render(
    int x, 
	int y, 
	SDL_Rect* crop, 
	double angle, 
	SDL_Point* center, 
	SDL_RendererFlip flip) {

	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, _width, _height};

	//Set clip rendering dimensions
	if (crop != NULL) {
		renderQuad.w = crop->w;
		renderQuad.h = crop->h;
	}

	SDL_RenderCopyEx(_renderer, _texture, crop, &renderQuad, angle, center, flip );
}

SDL_Texture* Font::getTexture() {
	return _texture;
}

std::size_t Font::getWidth() {
	return _width;
}
std::size_t Font::getHeight() {
	return _height;
}