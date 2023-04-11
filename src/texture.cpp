#include <iostream>

#include "texture.h"

Texture::Texture(SDL_Renderer* renderer): _renderer(renderer) {
	_texture = NULL;
	_width = 0;
	_height = 0;
}

Texture::~Texture() {
	//Renderer shall be released only at the end
	releaseTexture();
	_renderer = NULL;
}

//Copy constructor
Texture::Texture(const Texture &source) {
	std::cout << "Texture: Copy constructor called." << std::endl;
	_texture = NULL;
	_renderer = source._renderer;
	_width = 0;
	_height = 0;
}

//Copy assignment operator
Texture &Texture::operator=(const Texture &source) {
	std::cout << "Texture: Copy assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
	_texture = NULL;
	_renderer = source._renderer;
	_width = 0;
	_height = 0;
}

//Move constructor
Texture::Texture(Texture &&source) {
	std::cout << "Texture: Move constructor called." << std::endl;
	_texture = source._texture;
	_renderer = source._renderer;
	_width = source._width;
	_height = source._height;
	source._texture = NULL;
	source._renderer = NULL;
	source._width = 0;
	source._height = 0;
}

//Move assignment operator
Texture &Texture::operator=(Texture &&source) {
	std::cout << "Texture: Move assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
	_texture = source._texture;
	_renderer = source._renderer;
	_width = source._width;
	_height = source._height;
	source._texture = NULL;
	source._renderer = NULL;
	source._width = 0;
	source._height = 0;
}

void Texture::releaseTexture() {
	//Free texture if it exists
	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
		_texture = NULL;
		_width = 0;
		_height = 0;
	}
}

void Texture::loadFromFile(std::string path) {
	//Get rid of preexisting texture
	releaseTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_LogMessage(
		SDL_LOG_CATEGORY_APPLICATION, 
		SDL_LOG_PRIORITY_INFO, 
		"Loading: %s", 
		path.c_str());
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
        std::cerr << "Unable to load image from: " << path.c_str() << std::endl;
        std::cerr << "SDL2_IMG_Error: " << IMG_GetError() << std::endl;
	}

	//Color key image (for making BG Color transparent)
	SDL_SetColorKey( 
		loadedSurface, 
		SDL_TRUE, 
		SDL_MapRGB(
			loadedSurface->format, 
			0x8C, 
			0xFF, 
			0xFB));

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    
    if (newTexture == NULL) {
        std::cerr << "Unable to create texture from: " << path.c_str() << std::endl;
        std::cerr << "SDL2_Error: " << SDL_GetError() << std::endl;
    } else {
		_width = loadedSurface->w;
		_height = loadedSurface->h;
	}

    SDL_FreeSurface(loadedSurface);

	_texture = newTexture;
}

void Texture::render(
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

	SDL_RenderCopyEx(_renderer, _texture, crop, &renderQuad, angle, center, flip);
}

SDL_Texture* Texture::getTexture() {
	return _texture;
}

std::size_t Texture::getWidth() {
	return _width;
}
std::size_t Texture::getHeight() {
	return _height;
}